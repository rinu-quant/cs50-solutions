import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

app = Flask(__name__)

app.jinja_env.filters["usd"] = usd

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    cash_row = db.execute("SELECT cash FROM users WHERE id = ? ",session["user_id"])
    cash = cash_row[0]["cash"]

    holdings = db.execute("SELECT symbol,SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",session["user_id"])
    grand_total = cash

    for stock in holdings :
        quote = lookup(stock["symbol"])
        price = quote["price"]

        stock["price"] = price
        stock["total"] = price * stock["total_shares"]

        grand_total += stock["total"]

    return render_template("index.html",portfolio = holdings ,cash = float(cash) ,grand_total = float(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if "user_id" not in session :
        return redirect("/login")
    
    if request.method == "GET" :
        return render_template("buy.html")
    else :
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        result = lookup(symbol)

        if not symbol :
            return apology("must provide a symbol")
        if result is None :
            return apology("symbol not found")
        if not shares:
            return apology("must buy atleast 1 share")
        try:
            shares = int(shares)
        except ValueError :
            return apology("shares must be integer")
        if shares < 0 :
            return apology("shares must be positive integer")
        
        price = result["price"]
        req_cash = shares*price
        row = db.execute("SELECT cash FROM users WHERE id = ? ",session["user_id"])
        user_cash = row[0]["cash"]

        if req_cash > user_cash :
            return apology("not enough cash") 
        else :
            db.execute("INSERT INTO transactions(user_id,symbol,price,shares) VALUES(?,?,?,?) ", session["user_id"],symbol,price,shares)
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ? ",req_cash,session["user_id"])
            flash("BROUGHT!")
            return redirect("/") 
        


@app.route("/history")
@login_required
def history():
    if "user_id" not in session :
        return redirect("/login")
    
    transactions = db.execute("SELECT symbol,shares,price,time FROM transactions WHERE user_id = ? ORDER BY time DESC",session["user_id"])

    return render_template("history.html",transactions = transactions)


@app.route("/login", methods=["GET", "POST"])
def login():

    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():

    session.clear()

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if "user_id" not in session :
        return redirect("/login")
    
    if request.method == "POST" :

        symbol = request.form.get("symbol").strip().upper()
        result = lookup(symbol)

        if result is None :
            return apology("Invalid Symbol", 403)
        else:
            return render_template("quoted.html",result = result)
        
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        hash = generate_password_hash(password)

        if not username:
            return apology("must provide username")
        if not password:
            return apology("must provide password")
        if password != confirmation:
            return apology("password doesn't match")
        
        try:
            db.execute("INSERT INTO users (username,hash) VALUES (?,?)",username,hash)
        except ValueError:
            return apology("username already exists")


        rows = db.execute("SELECT * FROM users WHERE username = ? ",username)
        session["user_id"] = rows[0]["id"]

        return redirect ("/")

    else:
        
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST" :
        symbol = request.form.get("symbol").strip().upper()
        shares = int(request.form.get("shares"))
        if not symbol :
            return apology("must povide a symbol")
        row = db.execute("SELECT SUM(shares) AS total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol HAVING total_shares > 0",session["user_id"],symbol)
        if len(row) != 1 or row[0]["total_shares"] < shares:
            return apology("not enoudh shares")
        
        stock = lookup(symbol)
        price = stock["price"]
        sell_price = shares * price

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ? ",sell_price,session["user_id"])
        db.execute("INSERT INTO transactions (user_id,symbol,shares,price) VALUES (?,?,?,?) ",session["user_id"],symbol,-shares,price)
        flash("SOLD!")

        return redirect("/")


    else :
        holdings = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",session["user_id"])
        return render_template("sell.html",holdings = holdings)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    if request.method == "GET" :
        return render_template("password.html")
    else :
        old_pass = request.form.get("current")
        new_pass = request.form.get("new")
        confirm_pass = request.form.get("confirm")

        if not old_pass:
            return apology("must provide old password")
        if not new_pass:
            return apology("must provide new password")
        if new_pass != confirm_pass:
            return apology("password doesn't match")

        rows = db.execute("SELECT * FROM users WHERE id = ? ",session["user_id"])
        if not check_password_hash(rows[0]["hash"], old_pass):
            return apology("wrong password entered")

        new_hash = generate_password_hash(new_pass)
        db.execute("UPDATE users SET hash = ? WHERE id = ? ",new_hash,session["user_id"])
        flash("Password Updated!")
        return redirect("/")




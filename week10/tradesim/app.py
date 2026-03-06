from engine import engine
from flask import Flask, render_template , request  

app = Flask(__name__)

trade_history = []

@app.route("/" , methods = ["GET" , "POST"] )
def index():
        if request.method == "POST" :
 
                stock = request.form.get("stock")
                strategy = request.form.get("strategy")
                capital = float(request.form.get("capital"))
                start_date = request.form.get("start_date")
                end_date = request.form.get("end_date")

                final_capital , history = engine(stock,capital,strategy,start_date,end_date)

                global trade_history
                trade_history = history

                return render_template("result.html" , final_capital = final_capital)
        else :
                return render_template("index.html")
        
@app.route("/history")
def history():
        return render_template("history.html" , history = trade_history )
        
if __name__ == "__main__" :
    app.run(debug = True)








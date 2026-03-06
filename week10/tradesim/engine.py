import pandas as pd
from strategy import momentum_strategy , mean_reversion , rsi_strategy

def engine(stock,capital,strategy,start_date,end_date) :

    filename = f"data/{stock}.csv"
    data = pd.read_csv(filename)

    data["Date"] = pd.to_datetime(data["Date"])
    start_date = pd.to_datetime(start_date)
    end_date = pd.to_datetime(end_date)

    data = data[ (data["Date"] >= start_date) & (data["Date"] <= end_date) ].reset_index(drop=True)

    strategies = { "Momentum" : momentum_strategy ,
                 "Mean_Reversion" : mean_reversion ,
                 "RSI_Strategy" : rsi_strategy 
                }
    if strategy in strategies :
        data = strategies[strategy](data)
    else :
        raise ValueError("Invalid strategy selected")

    shares = 0
    history = []

    for i in range(len(data)):

        price = data["Close"].iloc[i]
        date = data["Date"].iloc[i]
        signal = data["Signal"].iloc[i]

        if signal == 1 and capital > price:
            shares = capital // price
            capital -= shares * price

            history.append({
                "date": date,
                "action": "BUY",
                "price": price,
                "shares": shares
            })

        elif signal == -1 and shares > 0:
            capital += shares * price

            history.append({
                "date": date,
                "action": "SELL",
                "price": price,
                "shares": shares
            })

            
        if shares > 0 : 
            final_price = data["Close"].iloc[-1]
            capital += shares * final_price

    return capital , history








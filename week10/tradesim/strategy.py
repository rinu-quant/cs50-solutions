

def momentum_strategy(data):

    data["Signal"] = 0

    for i in range(1,len(data)) :
        if data["Close"].iloc[i] > data["Close"].iloc[i-1] :
            data.loc[i,"Signal"] = 1
        elif data["Close"].iloc[i] < data["Close"].iloc[i-1] :
            data.loc[i,"Signal"] = -1

    return data        





def mean_reversion(data):

    data["Signal"] = 0

    rolling_mean = data["Close"].rolling(window=20).mean()

    for i in range(20, len(data)):

        price = data["Close"].iloc[i]
        mean = rolling_mean.iloc[i]

        if price < mean * 0.98:
            data.loc[i, "Signal"] = 1

        elif price > mean * 1.02:
            data.loc[i, "Signal"] = -1

    return data






def rsi_strategy(data):

    data["Signal"] = 0
    delta = data["Close"].diff()
    gain = delta.clip(upper=0)
    loss = -delta.clip(lower=0)

    avg_gain = gain.rolling(window=14).mean()
    avg_loss = loss.rolling(window=14).mean()

    rs = avg_gain / avg_loss
    rsi = 100 - ( 100 / ( 1 +rs ) )

    for i in range(14,len(data)) :
        if rsi.iloc[i] < 30 :
            data.loc[i,"Signal"] = 1
        elif rsi.iloc[i] > 70 :
            data.loc[i,"Signal"] = -1

    return data

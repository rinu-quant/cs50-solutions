                                     Backtesting Engine

# Description:

This project is a Backtesting Engine that simulates trading strategies on historical stock data. The main purpose of this project is to understand how different strategies perform over a specified period and how capital would change if those strategies were applied.

The engine allows the user to select a stock, define a strategy, set the capital amount, and specify the date range for the backtest. Once executed, the engine simulates buying and selling according to the chosen strategy and keeps track of trades, displaying the final capital and trade history.

The project has a web interface built using Flask, which provides a simple and interactive way to run backtests without needing to touch the code. Users can select from three strategies: Momentum, Mean Reversion, and RSI. The interface allows entering the starting capital, the stock, and the date range. After running the backtest, the results and trade history are displayed in a clean format.

# Momentum Strategy
The Momentum Strategy buys when the price is trending upward compared to the previous day and sells when the trend reverses. The strategy uses a simple signal based on the price difference between consecutive days. This strategy works under the assumption that strong trends continue for some time.

# Mean Reversion Strategy
The Mean Reversion Strategy relies on the concept that prices often revert to their average over time. It calculates a rolling mean over a window of days and generates a buy signal when the price falls below the mean, and a sell signal when it rises above the mean. This strategy is useful for markets where prices oscillate around a stable average.

# RSI Strategy
The RSI (Relative Strength Index) Strategy is based on momentum indicators. It calculates the RSI over a set period and generates buy signals when the RSI is below a certain threshold (indicating oversold conditions) and sell signals when it is above another threshold (indicating overbought conditions). This strategy allows for more nuanced entries and exits compared to simple momentum or mean reversion.

The project consists of multiple files:
- engine.py: Contains the engine function that runs the backtest, applies the chosen strategy, calculates buy/sell signals, and tracks the capital and shares over time.
- strategy.py: Contains the logic for all three strategies. Each strategy generates signals for the engine to act upon.
- app.py: Handles the web interface using Flask, receives user inputs from the front-end, runs the engine, and renders the results.
- templates/: Contains HTML templates for index, results, and trade history.
- static/: Contains CSS files for styling the web interface.

The design choices focused on modularity and simplicity. Each strategy is independent, making it easy to add or modify strategies without affecting the rest of the code. The engine is separated from the web interface, so it can be reused or extended for more advanced backtesting in the future.

In conclusion, this project provides an interactive and visual way to test trading strategies on historical data. It demonstrates basic concepts of algorithmic trading, backtesting, and strategy evaluation in a simple yet effective format.

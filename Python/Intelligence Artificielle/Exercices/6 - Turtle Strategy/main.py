
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

bitcoin = pd.read_csv("BTC-EUR.csv", index_col="Date", parse_dates=True)

plt.figure(figsize=(12,8))
plt.subplot(2,1,1)
bitcoin.loc["2019", "Close"].plot(label="dose")
bitcoin.loc["2019", "Close"].rolling(window=28, center=False).min().plot(label="min")
bitcoin.loc["2019", "Close"].rolling(window=28, center=False).max().plot(label="max")
plt.legend()

bitcoin["Buy"] = np.zeros(len(bitcoin))
bitcoin["Sell"] = np.zeros(len(bitcoin))

bitcoin["Sell"][bitcoin["Close"] <= bitcoin["Close"].rolling(window=28).min()] = -1
bitcoin["Buy"][bitcoin["Close"] >= bitcoin["Close"].rolling(window=28).max()] = 1

plt.subplot(2,1,2)
bitcoin.loc["2019", "Buy"].plot(label="Buy", color="g")
bitcoin.loc["2019", "Sell"].plot(label="Sell", color="r")
plt.legend()

plt.show()
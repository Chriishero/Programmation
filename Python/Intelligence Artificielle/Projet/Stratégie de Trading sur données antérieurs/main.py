
import numpy as np
import matplotlib.pyplot as plt 
import pandas as pd

crypto = pd.read_csv("sol-usd-max.csv", index_col="snapped_at", parse_dates=True)
print(crypto.head())

plt.figure(figsize=(12,8))
plt.subplot(2,1,1)

min = crypto['price'].resample("2D").min()
max = crypto['price'].resample("2D").max()
crypto.loc["09-2024", 'price'].plot(label='dose')
min['09-2024'].plot(label='min')
max['09-2024'].plot(label='max')
plt.legend()

crypto["Buy"] = np.zeros(len(crypto))
crypto["Sell"] = np.zeros(len(crypto))

crypto["Buy"][crypto["price"] <= crypto['price'].shift(1)] = 1
crypto["Sell"][crypto["price"] >= crypto['price'].shift(1)] = -1

plt.subplot(2,1,2)
crypto.loc["09-2024", 'Buy'].plot(label='Buy', color='g')
crypto.loc["09-2024", 'Sell'].plot(label='Sell', color='r')
plt.legend()
plt.show()
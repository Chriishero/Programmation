
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.pipeline import make_pipeline
from sklearn.linear_model import SGDClassifier
from sklearn.preprocessing import PolynomialFeatures, RobustScaler, OneHotEncoder
from sklearn.model_selection import train_test_split, GridSearchCV

crypto = pd.read_csv("sol-usd-max.csv", index_col="snapped_at", parse_dates=True)
crypto.dropna(axis=0, inplace=True)
crypto["date"] = crypto.index
crypto['date'].astype('category').cat.codes
crypto['price'].astype('category').cat.codes

X = crypto["2023":"2024"]["date"].to_frame()
y = crypto["2023":"2024"]["price"]
print(X.head())
print(y.head())

X_train, X_test, y_train, y_test = train_test_split(X, y)
print("divisé")
model = SGDClassifier()

model.fit(X_train, y_train)
print("grid fit")
print("Score: ", model.score(X_test, y_test))
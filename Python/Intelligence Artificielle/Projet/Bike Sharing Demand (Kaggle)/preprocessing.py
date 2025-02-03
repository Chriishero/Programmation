"""
AIDE À L'ANALYSE : 
https://www.kaggle.com/code/pmarcelino/comprehensive-data-exploration-with-python/notebook
"""

import numpy as np 
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.pipeline import make_pipeline
from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemble import RandomForestRegressor, GradientBoostingRegressor, BaggingRegressor, StackingRegressor, VotingRegressor
from sklearn.model_selection import learning_curve
from sklearn.preprocessing import PowerTransformer, PolynomialFeatures, RobustScaler, StandardScaler, MinMaxScaler, OneHotEncoder
from sklearn.feature_selection import SelectKBest, f_regression
from sklearn.metrics import *
from sklearn.compose import make_column_selector, make_column_transformer
from sklearn.impute import KNNImputer, SimpleImputer
from scipy import stats # probplot
from scipy.stats import norm
from sklearn.linear_model import LinearRegression, Lasso, Ridge
from sklearn.svm import SVR

trainset = pd.read_csv("set/train.csv")
y_test = pd.read_csv("set/sampleSubmission.csv")
testset = pd.read_csv("set/test.csv")
y_test = y_test.drop('datetime', axis=1)

testset = pd.concat([testset, y_test], axis=1)
trainset = trainset[testset.columns]

trainset, testset = train_test_split(trainset, test_size=0.2, random_state=0)

def select_var(df):
    df = df.drop("atemp", axis=1)

    return df

def feature_engineering(df):
    df['datetime'] = pd.to_datetime(df['datetime'])

    df["hour"] = df["datetime"].dt.hour
    df["day_of_week"] = df["datetime"].dt.dayofweek
    df["month"] = df["datetime"].dt.month
    df["year"] = df["datetime"].dt.year

    df = df.set_index("datetime")
    print(df.head())

    return df

def encodage(df):
    """continuous_var = df.drop(["season", "holiday", "workingday", "weather", "count"], axis=1).columns

    transformer = MinMaxScaler()
    df[continuous_var] = transformer.fit_transform(df[continuous_var])"""

    return df

def transform(df):
    df["count"] = np.sqrt(df["count"])
    df["temp"] = np.sqrt(df["temp"])
    pt = PowerTransformer(method="yeo-johnson")
    df["windspeed"] = pt.fit_transform(df["windspeed"].values.reshape(-1, 1))

    return df

def preprocessing(df):
    df = select_var(df)
    df = feature_engineering(df)
    df = encodage(df)
    df = transform(df)

    X = df.drop("count", axis=1)
    y = df["count"]

    return X, y

def inverse_transform(X_test, y_test, y_pred):
    X_test["temp"] = X_test["temp"] ** 2
    y_test = y_test ** 2
    y_pred = y_pred ** 2

    return X_test, y_test, y_pred

def save_set(X_train, y_train, X_test, y_test):
    X_train.to_csv("set/X_train.csv", index=True)
    y_train.to_csv("set/y_train.csv", index=True)
    X_test.to_csv("set/X_test.csv", index=True)
    y_test.to_csv("set/y_test.csv", index=True)

X_train, y_train = preprocessing(trainset)
X_test, y_test = preprocessing(testset)

save_set(X_train=X_train, y_train=y_train, X_test=X_test, y_test=y_test)

tree = DecisionTreeRegressor(min_samples_leaf=100)
model = make_pipeline(PolynomialFeatures(1), GradientBoostingRegressor())

def evaluation(model):
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    X_test_notrans, y_test_notrans, y_pred_notrans = inverse_transform(X_test, y_test, y_pred)

    N, train_score, val_score = learning_curve(model, X_train, y_train, cv=4, train_sizes=np.linspace(0.1, 1, 10))

    plt.figure(figsize=(12,8))
    plt.plot(N, train_score.mean(axis=1), label="Train Score")
    plt.plot(N, val_score.mean(axis=1), label="Validation Score")
    plt.title(f"Score : {model.score(X_train, y_train)} | RMSE : {np.sqrt(mean_squared_error(y_test_notrans, y_pred_notrans))}")
    plt.legend()

evaluation(model)

plt.show()

"""
AIDE À L'ANALYSE : 
https://www.kaggle.com/code/pmarcelino/comprehensive-data-exploration-with-python/notebook
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.pipeline import make_pipeline
from sklearn.model_selection import learning_curve, GridSearchCV, RandomizedSearchCV
from sklearn.metrics import *
from sklearn.preprocessing import PolynomialFeatures
from sklearn.feature_selection import SelectKBest, SelectFromModel, f_regression, mutual_info_regression
from sklearn.linear_model import LinearRegression
from sklearn.svm import SVR
from sklearn.ensemble import GradientBoostingRegressor, RandomForestRegressor, BaggingRegressor, VotingRegressor, StackingRegressor
from sklearn.tree import DecisionTreeRegressor, ExtraTreeRegressor
from lightgbm import LGBMRegressor
from xgboost import XGBRegressor
from catboost import CatBoostRegressor

X_train = pd.read_csv("set/X_train.csv", index_col="datetime", parse_dates=True)
y_train = pd.read_csv("set/y_train.csv", index_col="datetime", parse_dates=True)
X_test = pd.read_csv("set/X_test.csv", index_col="datetime", parse_dates=True)
y_test = pd.read_csv("set/y_test.csv", index_col="datetime", parse_dates=True)

y_train = y_train.values.ravel()
y_test = y_test.values.ravel()

model = make_pipeline(PolynomialFeatures(1), GradientBoostingRegressor(loss='squared_error', learning_rate=0.1, n_estimators=350, subsample=0.2, min_samples_split=30, 
                                                                       min_samples_leaf=40, max_depth=10, init=None, random_state=0, max_features=None, 
                                                                       alpha=0.9, verbose=5, max_leaf_nodes=None, warm_start=False))
# 0.971, 41.9, quasi aucun overfitting : 0.970-0.955


model = make_pipeline(PolynomialFeatures(2), LGBMRegressor(boosting_type='gbdt', num_leaves=50, max_depth=8, learning_rate=0.1, n_estimators=500, 
                                                           subsample_for_bin=200000, objective=None, class_weight=None, min_split_gain=0.1, min_child_weight=0.001, 
                                                           min_child_samples=20, subsample=1.0, subsample_freq=0, colsample_bytree=1.0, reg_alpha=0, 
                                                           reg_lambda=0, random_state=0, n_jobs=None, importance_type='split'))
# 99.5 37.2 avec léger overfitting : 0.995 - 0.960


def inverse_transform(X_test, y_test, y_pred):
    X_test["temp"] = X_test["temp"] ** 2
    y_test = y_test ** 2
    y_pred = y_pred ** 2

    return X_test, y_test, y_pred

def evaluation(model):
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    X_test_notrans, y_test_notrans, y_pred_notrans = inverse_transform(X_test, y_test, y_pred)

    N, train_score, val_score = learning_curve(model, X_train, y_train, cv=4, train_sizes=np.linspace(0.1, 1, 10))

    plt.figure(figsize=(12,8))
    plt.plot(N, train_score.mean(axis=1), label="Train Score")
    plt.plot(N, val_score.mean(axis=1), label="Validation Score")
    plt.title(f"Score : {model.score(X_train, y_train)} | RMSE : {root_mean_squared_error(y_test_notrans, y_pred_notrans)}")
    plt.legend()

    plt.figure(figsize=(12,8))
    plt.scatter(X_test_notrans.index, y_test_notrans, label="y_test")
    plt.scatter(X_test_notrans.index, y_pred_notrans, label="y_pred")
    plt.title(f"Score : {model.score(X_train, y_train)} | RMSE : {root_mean_squared_error(y_test_notrans, y_pred_notrans)}")
    plt.legend()

evaluation(model)

plt.show()

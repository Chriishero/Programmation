"""
AIDE À L'ANALYSE : 
https://www.kaggle.com/code/pmarcelino/comprehensive-data-exploration-with-python/notebook
"""

import numpy as np 
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.pipeline import make_pipeline
from sklearn.linear_model import LinearRegression, Lasso, ElasticNet, Ridge, RANSACRegressor
from sklearn.neighbors import RadiusNeighborsRegressor, KNeighborsRegressor
from sklearn.tree import DecisionTreeRegressor, ExtraTreeRegressor
from sklearn.model_selection import learning_curve, GridSearchCV, RandomizedSearchCV
from sklearn.feature_selection import SelectKBest, f_regression, mutual_info_regression
from sklearn.preprocessing import PolynomialFeatures
from sklearn.metrics import *
from sklearn.ensemble import AdaBoostRegressor, VotingRegressor, GradientBoostingRegressor, RandomForestRegressor, BaggingRegressor, StackingRegressor
from preprocessing import get_XY_set, inverse_transformation
from sklearn.preprocessing import RobustScaler
from lightgbm import LGBMRegressor
from xgboost import XGBRegressor
from catboost import CatBoostRegressor

X_train, y_train, X_test, y_test = get_XY_set()

model_1 = XGBRegressor()
model_2 = LGBMRegressor(n_estimators=200)
model_3 = CatBoostRegressor(n_estimators=200, max_depth=1)


model_10 = StackingRegressor([("XGBRegressor", model_1),
                            ("LGBMRegressor", model_2), 
                            ("CatBoostRegressor", model_3)], final_estimator=model_1)
#model_10 = GradientBoostingRegressor(n_estimators=50)

def evaluation(model):
    model.fit(X_train, y_train)

    y_pred = model.predict(X_test)

    N, train_score, val_score = learning_curve(model, X_train, y_train, cv=4, train_sizes=np.linspace(0.1, 1, 10))

    plt.figure(figsize=(12,8))
    plt.plot(X_test["Id"], y_test, label="test value")  
    plt.plot(X_test["Id"], y_pred, label="pred value")
    plt.title(f"{model.__class__.__name__} | Score : {model.score(X_test, y_test)} | RMSE : {np.sqrt(mean_squared_error(y_test, y_pred))}")
    plt.legend()

    plt.figure(figsize=(12,8))
    plt.plot(N, train_score.mean(axis=1), label='train_score')
    plt.plot(N, val_score.mean(axis=1), label='val_score')
    plt.title(f"{model.__class__.__name__}")
    plt.legend()

    print("train_score : ", train_score.mean(axis=1))
    print("val_score : ", val_score.mean(axis=1))


model = make_pipeline(PolynomialFeatures(3), SelectKBest(f_regression, k=15), RandomForestRegressor(n_estimators=100, max_depth=1))

evaluation(model)

plt.show()
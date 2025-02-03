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
from sklearn.ensemble import RandomForestRegressor, GradientBoostingRegressor, StackingRegressor, VotingRegressor
from sklearn.model_selection import learning_curve
from sklearn.preprocessing import PolynomialFeatures, RobustScaler, StandardScaler, MinMaxScaler, OneHotEncoder
from sklearn.feature_selection import SelectKBest, f_regression
from sklearn.metrics import *
from sklearn.compose import make_column_selector, make_column_transformer
from sklearn.impute import KNNImputer, SimpleImputer
from scipy import stats # probplot
from scipy.stats import norm

"""
pd.set_option("display.max_row", 111) # affiche toutes les lignes
pd.set_option("display.max_columns", 111)"""

dataset_train = pd.read_csv("train.csv")
X_test = pd.read_csv("test.csv")
y_test = pd.read_csv("sample_submission.csv")
trainset = dataset_train.copy()
testset = pd.concat([X_test, y_test["SalePrice"]], axis=1)

print((trainset.isna().sum()/trainset.shape[0]).sort_values(ascending=False))

important_columns = ["SalePrice", "GrLivArea", "TotalBsmtSF"]

def select_var(df, taux_nan, taux_var, taux_corr, columns_to_keep):
    if columns_to_keep is None:
        print("shape no NaNfilter : ", df.shape)
        low_nan_var = df.columns[df.isna().sum()/df.shape[0] < taux_nan]

        df_filtered = df[low_nan_var]
        print("shape NaNfilter : ", df_filtered.shape)
        qualitative_var = df_filtered.select_dtypes("object")

        var = df_filtered.select_dtypes(["float64", "int8", "int64"]).var()
        high_var_var = var[var > taux_var].index
        df_var_filtered = df[high_var_var] 
        if taux_var != 0:
            df_filtered = df_var_filtered
        print("shape variance filter : ", df_filtered.shape)

        corr = df_filtered.select_dtypes(["float64", "int8", "int64"]).corrwith(df["SalePrice"])
        high_corr_var = corr[corr.abs() > taux_corr].index
        if taux_corr == 0:
            high_corr_var = df_filtered
        
        df = df[list(high_corr_var) + list(qualitative_var) + ["Id"]]
    else:
        df = df[list(columns_to_keep) + ["SalePrice"]]

    return df

def encodage(df):
    df = df.copy()
    for col in df.select_dtypes("object"):
        df[col] = df[col].astype("category").cat.codes
        df[col] = df[col].replace(-1, np.nan) # remplace le code '-1' attribué au NaN, par un NaN

    """
    # N'améliore pas le dataset : 
    quantitative_var = df.select_dtypes(["float64", "int8", "int64"]).columns
    df[quantitative_var] = RobustScaler().fit_transform(df[quantitative_var])"""

    return df

def imputation(df):
    quantitative_var = df.select_dtypes(["float64", "int8", "int64"]).columns
    #df = df.dropna(axis=0)
    df = df.dropna(axis=0) # supprime les colonnes ayant au moins 1 NaN

    #df = df.drop(df[df["Id"] == 1299].index, axis=0) # supprime les outliers
    #df = df.drop(df[df["Id"] == 524].index, axis=0)

    #df[quantitative_var] = SimpleImputer(strategy="mean").fit_transform(df[quantitative_var])

    return df

def transformation(X, y):
    y = np.log(y)
    X["GrLivArea"] = np.log(X["GrLivArea"])
    X["TotalBsmtSF"] = np.log(X["TotalBsmtSF"])
    """X["HasBsmt"] = pd.Series(len(X["TotalBsmtSF"]), index=X.index)
    X["HasBsmt"] = 0
    X.loc[X["TotalBsmtSF"] > 0, "HasBsmt"] = 1 # crée un masque binaire, si area > 0 alors c'est 1, sinon 0
    X.loc[X["HasBsmt"] == 1, "TotalBsmtSF"] = np.log(X["TotalBsmtSF"])"""

    return X, y

def preprocessing(df, columns_to_keep):
    df = select_var(df=df, taux_nan=0.15, taux_var=0, taux_corr=0.2, columns_to_keep=columns_to_keep) # 0.025
    df = encodage(df)
    df = imputation(df)
    
    X = df.drop("SalePrice", axis=1)
    y = df["SalePrice"]

    X, y = transformation(X, y)

    return X, y

X_train, y_train = preprocessing(trainset, None)
X_test, y_test = preprocessing(testset, X_train.columns)

def get_XY_set():
    return X_train, y_train, X_test, y_test

print("xtrainshape : ", X_train.shape)
print("xtestshape : ", X_test.shape) # testset avec moins de colonne (features) que le trainset
print("ytrainshape : ", y_train.shape)
print("ytestshape : ", y_test.shape)

model = make_pipeline(PolynomialFeatures(3), SelectKBest(f_regression, k=10), RandomForestRegressor(n_estimators=100, max_depth=1))

def inverse_transformation(y_test, y_pred):
    y_test_transformed = np.exp(y_test)
    y_pred_transformed = np.exp(y_pred)

    return y_test_transformed, y_pred_transformed

def evaluation(model):
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    # y_test_transformed, y_pred_transformed = inverse_transformation(y_test, y_pred)

    N, train_score, val_score = learning_curve(model, X_train, y_train, cv=4, train_sizes=np.linspace(0.1, 1, 10))

    plt.figure(figsize=(12,8))
    plt.plot(X_test["Id"], y_test, label="test value")
    plt.plot(X_test["Id"], y_pred, label="pred value")
    plt.title(f"Score : {model.score(X_test, y_test)} | RMSE : {np.sqrt(mean_squared_error(y_test, y_pred))}")
    plt.legend()

    plt.figure(figsize=(12,8))
    plt.plot(N, train_score.mean(axis=1), label='train_score')
    plt.plot(N, val_score.mean(axis=1), label='val_score')
    plt.legend()

#evaluation(model)

plt.show()

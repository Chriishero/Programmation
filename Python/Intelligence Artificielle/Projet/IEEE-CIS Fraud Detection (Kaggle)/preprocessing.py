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
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier, BaggingClassifier
from sklearn.neighbors import KNeighborsClassifier
from lightgbm import LGBMClassifier
from xgboost import XGBClassifier
from catboost import CatBoostClassifier
from sklearn.model_selection import learning_curve
from sklearn.preprocessing import PowerTransformer, PolynomialFeatures, RobustScaler, StandardScaler, MinMaxScaler, OneHotEncoder
from sklearn.feature_selection import SelectKBest, f_regression, f_classif, chi2, mutual_info_classif
from sklearn.metrics import *
from sklearn.compose import make_column_selector, make_column_transformer
from sklearn.impute import KNNImputer, SimpleImputer
from sklearn.decomposition import PCA
from scipy import stats # probplot
from scipy.stats import norm
from sklearn.svm import SVC
from sklearn.utils import resample # permet de faire du rééchantillonage
import warnings

# Désactiver les avertissements spécifiques à la constante
warnings.filterwarnings("ignore", category=UserWarning, message="Features.*are constant.")
warnings.filterwarnings("ignore", category=RuntimeWarning, message="invalid value encountered in divide")

train_id = pd.read_csv("set/train_identity.csv")
train_trans = pd.read_csv("set/train_transaction.csv")
test_id = pd.read_csv("set/test_identity.csv")
test_trans = pd.read_csv("set/test_transaction.csv")
print("dataset chargé")

dataset = pd.concat([train_id, train_trans], axis=1)
validation_set = pd.concat([test_id, test_trans], axis=1)

dataset.columns = [col.replace("_", "-") if "id_" in col else col for col in dataset.columns]

y_0 = dataset[dataset["isFraud"] == 0]
y_1 = dataset[dataset["isFraud"] == 1]

y_0_downsampled = resample(y_0, replace=False, n_samples=int(len(y_1)), random_state=0)
dataset = pd.concat([y_0_downsampled, y_1])

def encodage(df):
    print("début encodage")
    df = df.copy()
    for col in df.select_dtypes("object"):
        df[col] = df[col].astype("category").cat.codes
        df[col] = df[col].replace(-1, np.nan)

    df = pd.DataFrame(MinMaxScaler().fit_transform(df), columns=df.columns)
    return df

def select_var(df):
    print("début select_var")
    low_nan_var = df.columns[df.isna().sum()/df.shape[0] < 0.9]
    df = df[low_nan_var]
    #df = df.loc[:, df.nunique() > 1] # supprime les variables constantes

    """X = df.drop("isFraud", axis=1)

    select_kbest = SelectKBest(score_func=f_classif, k=50)
    X_selected_temp = select_kbest.fit_transform(X.fillna(X.mean()), df["isFraud"])
    selected_features = X.columns[select_kbest.get_support()]

    X = X[selected_features]
    df = df[X.columns.tolist() + ['isFraud']]"""

    df = df.loc[:, ~df.columns.duplicated()]

    return df

def feature_engineering(df):
    print("début feature_engineering")

    df["hour"] = (df["TransactionDT"] % 86400) / 3600
    df["day"] = df["TransactionDT"] // 86400
    df["weekday"] = df["day"] % 7

    return df

def imputation(df):
    print("début imputation")

    df = df.copy()
    #df = pd.DataFrame(KNNImputer(n_neighbors=1).fit_transform(df), columns=df.columns)
    #df = pd.DataFrame(SimpleImputer(strategy="median").fit_transform(df), columns=df.columns)

    delete_features = ["C1", "C2", "C5", "C6", "C9", "C11", "C13", "C14", "D1", "D11", "card2", "card3", "card4", "card5", "card6", "dist1"]
    for col in delete_features:
        if col in df.columns:
            df = df.drop(col, axis=1)

    V_columns = df[[col for col in df.columns if col.startswith("V")]]
    V_columns = V_columns.fillna(-999)

    V_columns_PCA = PCA(n_components=50).fit_transform(V_columns)

    pca_columns = pd.DataFrame(
        V_columns_PCA,
        columns=[f"PCA_V{i+1}" for i in range(V_columns_PCA.shape[1])]
    )
    
    df = pd.concat([df, pca_columns], axis=1)
    df = df.drop(columns=[col for col in df.columns if col.startswith("V")])
    df = df.replace(-999, np.nan)

    return df

def transform(df):
    print("début transform")

    if "TransactionDT" in df.columns:
        df["TransactionDT"] = np.sqrt(df["TransactionDT"])

    cbrt_col = ["C4", "C7", "C8", "C10", "C12", "D3", "D5", "D10"]
    for col in cbrt_col:
        if col in df.columns:
            df[col] = np.cbrt(df[col])

    pt = PowerTransformer(method="yeo-johnson")

    yeo_col = ["TransactionAmt", "D4", "D15"]
    for col in yeo_col:
        if col in df.columns:
            df[col]= pt.fit_transform(df[col].values.reshape(-1, 1))

    return df

def preprocessing(df):
    df = encodage(df)
    df = select_var(df)
    df = feature_engineering(df)
    df = imputation(df)
    df = transform(df)

    trainset, testset = train_test_split(df, test_size=0.2, random_state=0)

    X_train = trainset.drop("isFraud", axis=1)
    y_train = trainset["isFraud"]
    X_test = testset.drop("isFraud", axis=1)
    y_test = testset["isFraud"]

    return X_train, y_train, X_test, y_test

def inverse_transform(X_test, y_test, y_pred):
    print("début inverse transform")   

    if "TransactionDT" in X_test.columns:
        X_test["TransactionDT"] = X_test["TransactionDT"]**2

    cbrt_col = ["C4", "C7", "C8", "C10", "C12", "D3", "D5", "D10"]
    for col in cbrt_col:
        if col in X_test.columns:
            X_test[col] = X_test[col]**3

    return X_test, y_test, y_pred

def save_set(X_train, y_train, X_test, y_test):
    print('début save_set')
    X_train.to_csv("set/X_train.csv", index=True)
    y_train.to_csv("set/y_train.csv", index=True)
    X_test.to_csv("set/X_test.csv", index=True)
    y_test.to_csv("set/y_test.csv", index=True)

X_train, y_train, X_test, y_test = preprocessing(dataset)

save_set(X_train, y_train, X_test, y_test)

model = make_pipeline(LGBMClassifier(random_state=0, class_weight={0: 1, 1: 1}))

def evaluation(model):
    print("début évaluation")
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    X_test_inv, y_test_inv, y_pred_inv = inverse_transform(X_test, y_test, y_pred)

    print(confusion_matrix(y_test_inv, y_pred_inv))
    print(classification_report(y_test_inv, y_pred_inv))
    print("F1 Score : ", f1_score(y_test_inv, y_pred_inv, average='binary'))

    print("début learning curve")
    N, train_score, val_score = learning_curve(model, X_train, y_train, cv=4, train_sizes=np.linspace(0.1, 1, 10))

    print("début graph")
    plt.figure(figsize=(10, 6))
    plt.plot(N, train_score.mean(axis=1), label="Train Score")
    plt.plot(N, val_score.mean(axis=1), label="Validation Score")
    plt.title(f"F1 Score : {f1_score(y_test_inv, y_pred_inv, average='binary')}")
    plt.legend()

evaluation(model)

plt.show()

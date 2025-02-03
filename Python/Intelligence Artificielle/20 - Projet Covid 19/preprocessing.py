"""
1. Mettre les données dans un format propice au ML
    - Train / Test
    - Encodage
    - Nettoyage des NaN

Underfitting? :
    - PolynomialFeatures
    - Feature Engineering
    - Modèle plus complexe

Overfitting? :
    - Imputation / fillna
    - SelectFromModel
    - Régularisation

F1 : la précision et la sensibilité (recall) sont des métriques permettant de mesurer la proportion de faux positif (erreur type 1) et de faux négatif (2)
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.pipeline import make_pipeline
from sklearn.feature_selection import SelectKBest, f_classif
# SelectKBest : utilise un test statistique pour faire une sélection de variable
# f_classif : test ANOVA
from sklearn.preprocessing import PolynomialFeatures
from sklearn.decomposition import PCA
from sklearn.metrics import f1_score, confusion_matrix, classification_report
# f1_score : rapport précision/sensibilité
# confusion_matrix : mesure la précision et la sensibilité
# classification_report : permet un bilan du recall, de la précision, du score f1, etc
from sklearn.model_selection import learning_curve # permettra de savoir si le modèle est en overfitting ou underfitting

pd.set_option("display.max_row", 111) # affiche toutes les lignes
pd.set_option("display.max_columns", 111)
dataset = pd.read_excel("dataset.xlsx")

df = dataset.copy()

missing_rate = df.isna().sum()/df.shape[0] # donne les différent taux de valeurs manquantes pour chaque variable
print(missing_rate)

blood_columns = list(df.columns[(missing_rate < 0.9) & (missing_rate > 0.88)]) # toutes les variables de type taux sangin
viral_columns = list(df.columns[(missing_rate < 0.80) & (missing_rate > 0.75)]) # toutes les variables de type test viral

key_columns = ["Patient age quantile", "SARS-Cov-2 exam result"]

df = df[key_columns + blood_columns + viral_columns] # filtre le dataframe en ne gardant que ces variables importantes
print(df.head())

trainset, testset = train_test_split(df, test_size=0.2, random_state=0) # crée un trainset et un testset

print(trainset["SARS-Cov-2 exam result"].value_counts()) # vérifie les propotions de positif et négatif (doit être à environ 10% ici)
print(testset["SARS-Cov-2 exam result"].value_counts())

def encodage(df): # fonction qui encode certaines catégorie
    code = {'positive':1, 'negative':0, 'detected':1, 'not_detected':0} # relie les catégories 'positive', 'negetive', 'detected', 'not_detected' à des valeurs

    for col in df.select_dtypes('object'):
        df[col] = df[col].map(code) # applique le dictionnaire 'code' (encodage) à toutes les colonnes de types 'object' de df
    
    return df

def feature_engineering(df):
    df["est malade"] = df[viral_columns].sum(axis=1) >= 1 # création d'une nouvelle variable qui dit si un patient est testé positif à au moins une maladie ou non
    df = df.drop(viral_columns, axis=1)
    return df

def imputation(df): # fonction qui supprime les valeurs manquantes
    """
    Ne marche pas ici : 
    df['is na'] = (df["Parainfluenza 3"].isna()) | (df["Leukocytes"].isna())
    df = df.fillna(-999)
    """

    df = df.dropna(axis=0)
    return df

def preprocessing(df): # applique les fonction de preprocessing et crée les variables X, y
    df = encodage(df)
    df = feature_engineering(df)
    df = imputation(df)

    X = df.drop("SARS-Cov-2 exam result", axis=1)
    y = df["SARS-Cov-2 exam result"]

    print(y.value_counts())

    return X, y

X_train, y_train = preprocessing(trainset)
X_test, y_test = preprocessing(testset)

def XY():
    return X_train, X_test, y_train, y_test

model = make_pipeline(PolynomialFeatures(2, include_bias=False), SelectKBest(f_classif, k=10), # sélectionne les 10 meilleurs variables selon le test ANOVA
                      RandomForestClassifier(random_state=0))

# Procédure d'évaluation
def evaluation(model):
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    print(confusion_matrix(y_test, y_pred))
    print(classification_report(y_test, y_pred))

    N, train_score, val_score = learning_curve(model, X_train, y_train, cv=4, scoring='f1', train_sizes=np.linspace(0.1, 1, 10))
    # np.linspace(0.1, 1, 10) : 0.1 à 1 avec 10 découpes

    plt.figure(figsize=(12,8))
    plt.plot(N, train_score.mean(axis=1), label='train score') # évolution de 'N' (nombre d'échantillon pour entrainer le modèle) et la moyenne du 'train_score'
    plt.plot(N, val_score.mean(axis=1), label='val score')
    plt.legend()
    # on peut voir que le modèle est en overfitting (trop de donnée), car le train_score est bon, mais le val_score mauvais

#evaluation(model)

#pd.DataFrame(model.feature_importances_, index=X_train.columns).plot(kind="bar", figsize=(12,8)) # crée une graphique de bar
# chaque valeur de 'feature_importances' aura une colonne associé dans ce tableau panda
plt.show()
"""
Un transformer entrainé sur un trainset, utilisera les mêmes valeurs sur le testset, ici les valeurs de remplacement.

SimpleImputer(missing_values=np.nan, strategy='mean') : spécifie les valeurs manquantes, ici 'np.nan', ainsi que la stratégie pour les remplacer, ici la moyenne
KNNImputer(n_neighbors=n) : remplace les valeurs manquantes, par les valeurs des plus proches voisins, en choisissant un nombre de voisins 'n'
MissingIndicator() : renvoie des booléens indiquant l'absence ou non de valeurs dans le dataset

strategy : mean, median, most_frequent, constant
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from sklearn.linear_model import SGDClassifier
from sklearn.impute import SimpleImputer, KNNImputer, MissingIndicator
from sklearn.pipeline import make_union, make_pipeline
from sklearn.model_selection import GridSearchCV, train_test_split

X_train = np.array([[10, 3], 
             [0, 4],
             [5, 3],
             [np.nan, 3]])

transformer = SimpleImputer(missing_values=np.nan, strategy='mean')
print("Trainset SimpleImputer : ", transformer.fit_transform(X_train))

X_test = np.array([[10, 32], 
             [50, 4],
             [5, 3],
             [np.nan, np.nan]])
print("Testset SimpleImputer : ", transformer.fit_transform(X_test))


X_train = np.array([[10, 3], 
             [50, 4],
             [82, 1],
             [np.nan, 3]])

transformer = KNNImputer(n_neighbors=1)
print("Trainset KNNImputer : ", transformer.fit_transform(X_train))

X_test = np.array([[10, 32], 
             [50, 4],
             [5, 3],
             [np.nan, np.nan]])
print("Testset KNNImputer : ", transformer.fit_transform(X_test))

pipeline = make_union(SimpleImputer(strategy="constant", fill_value=-99), MissingIndicator()) # remplace les valeurs manquantes par -99
print(pipeline.fit_transform(X_test))

titanic = sns.load_dataset("titanic")
X = titanic[["pclass", "age"]]
y = titanic['survived']

X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=1)

model = make_pipeline(KNNImputer(), SGDClassifier())
params = {
    "knnimputer__n_neighbors":[1,2,3,4]
}
grid = GridSearchCV(model, param_grid=params, cv=5)
grid.fit(X_train, y_train)
print(grid.best_params_)

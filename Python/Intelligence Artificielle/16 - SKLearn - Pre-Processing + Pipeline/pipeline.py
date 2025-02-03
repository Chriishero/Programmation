"""
Transformer : interface de programmation pour traiter l'ensemble des données, en transformant les données futures de la même manière qu'on était tranformé les données d'entrainement.
Pipeline : chaine de transformation, combination entre un transformer et un estimator.

La Pipeline permet de regrouper le transformer et l'estimator, ainsi que d'effectuer la transformation nécessaire sur toutes les variables lors de l'entrainement et la prédiction.

pipeline = make_pipeline(Transformer1, Model) : plusieurs transformer peuvent être mis
grid = GridSearchCV(pipeline, params, cv) : cross-validation avec la pipeline
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures, RobustScaler
from sklearn.linear_model import SGDClassifier
from sklearn.pipeline import make_pipeline
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split, GridSearchCV

iris = load_iris()
X = iris.data
y = iris.target

X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
model = make_pipeline(PolynomialFeatures(),
                      RobustScaler(),
                      SGDClassifier(random_state=0))

print(model) # permet de voir toutes les étapes du pipeline, ainsi que les hyperparamètres
params = {
    "polynomialfeatures__degree":[2,3,4],
    "sgdclassifier__penalty":['l1', 'l2']
}

grid = GridSearchCV(model, param_grid=params, cv=4)
grid.fit(X_train, y_train)
print("Meilleur paramètres : ", grid.best_params_)
print("Meilleur paramètres : ", grid.best_score_)

model = SGDClassifier(random_state=0)
model.fit(X_train, y_train)
print("Score sans Pre-Processing : ", model.score(X_test, y_test))

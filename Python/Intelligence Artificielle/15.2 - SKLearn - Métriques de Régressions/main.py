"""
Erreur absolue moyenne (MAE) : fais la moyenne de la valeur absoulue de toutes les erreurs: 1/m∑|y_true - y_pred|
    À utiliser quand l'importance d'une erreur est linéaire avec son amplitude. C-à-d si le dataset contient des valeurs aberrantes (outliers)

Erreur quadratique moyenne (MSE) : fais la moyennne de toutes les erreurs au carré  : 1/m∑(y_true - y_pred)²
Racine carré de l'erreur quadratique moyenne (RMSE) : remet à l'échelle les erreurs calculé par la MAE
    À utiliser quand l'importance d'une erreur est exponentielle avec son amplitude. C-à-d quand on donne une grande importance aux grandes erreurs.
    La MSE pénalise beaucoup plus les grandes erreur que la MAE
    La MSE n'est PAS le carré de la MAE.

Erreur absolue médianne : trie dans l'ordre les valeurs, puis renvoie la médianne : median{|y_true - y_pred|}
    Très peu sensible aux grandes erreurs

Coefficient de détermination (R²) : évalue la performance du modèle par rapport au niveau de variation présent dans les données : 
    R² = 1 - Σ(y_true - y_pred)² / Σ(y_true - mean(y_true))² : R² = 1 - erreur quadratique / variance : proche de 1 = peu d'erreurs
    Est utilisé de base dans la méthode 'score(X, y)' de tous les estimateurs de régression : 

Structure des fonctions 'metrics' :
    metrics(y_true, y_pred) : y targets, prédictions de y
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.metrics import *
from sklearn.datasets import fetch_california_housing
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import cross_val_score

data_url = "http://lib.stat.cmu.edu/datasets/boston" # charge le dataset de l'immobilier de boston qui a été supprimé depuis la version 1.2 de SKLearn
raw_df = pd.read_csv(data_url, sep="\s+", skiprows=22, header=None)
X = np.hstack([raw_df.values[::2, :], raw_df.values[1::2, :2]])
y = raw_df.values[1::2, 2]

model = LinearRegression()
model.fit(X, y)
y_pred = model.predict(X)

print("MAE : ", mean_absolute_error(y, y_pred))
print("MSE : ", mean_squared_error(y, y_pred))
print("RMSE : ", np.sqrt(mean_squared_error(y, y_pred)))
print("Median abs err : ", median_absolute_error(y, y_pred))
print("Determination Coef : ", model.score(X, y)) # le modèle décrit 74% des variations du prix de l'immobilier à boston

score = cross_val_score(model, X, y, cv=3, scoring="neg_mean_absolute_error") # évalue le dataset avec la métrique MAE au lieu du coefficient de détermination
# string de toutes les métriques : https://scikit-learn.org/stable/modules/model_evaluation.html

print(score)

plt.figure(figsize=(10,10))
plt.subplot(211)
plt.scatter(X[:, 5], y, label='y')
plt.scatter(X[:, 5], y_pred, alpha=0.8, label='y_pred')
plt.legend()

plt.subplot(212)
err_hist = np.abs(y - y_pred)
plt.hist(err_hist, bins=50) # histogramme avec 50 intervals
# les erreurs suivent une loi de distribution exponentielle

plt.show()

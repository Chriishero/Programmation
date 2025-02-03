"""
Voting : permet d'entrainer une liste de modèle, puis de regrouper les résultats généraux
Bagging : crée plusieurs copies d'un même modèle, en entrainant chaque copie sur une partie aléatoire du dataset (en parallèle).
Boosting : modèles faibles entrainés sur tout le dataset qui essaye de corriger les erreurs de son prédécesseur (en série).
    AdaBoostClassifier(n_estimator=n)
    AdaBoostRegressor()
    GradientBoostingClassifier()
    GradientBoostingRegressor()
    À utiliser quand les modèles individuelles n'atteignent pas de bonnes performances.
Stacking : au lieu de rassembler les prédictions de chaque modèle, demande à un dernier estimateur d'apprendre à prédire le résultat final en fonction de ces prédictions
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split
from sklearn.ensemble import AdaBoostClassifier, GradientBoostingClassifier

X, y = make_moons(n_samples=500, noise=0.3, random_state=0)
plt.scatter(X[:, 0], X[:, 1], c=y)
plt.show()

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)

model = AdaBoostClassifier(n_estimators=100)
model.fit(X_train, y_train)
print(model.score(X_test, y_test))
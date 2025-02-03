"""
Voting : permet d'entrainer une liste de modèle, puis de regrouper les résultats généraux
Bagging : crée plusieurs copies d'un même modèle, en entrainant chaque copie sur une partie aléatoire du dataset (en parallèle).
Boosting : modèles faibles entrainés sur tout le dataset qui essaye de corriger les erreurs de son prédécesseur (en série).
Stacking : au lieu de rassembler les prédiciton de chaque modèle, demande à un dernier estimateur d'apprendre à prédire le résultat final en fonction de ces prédictions
    StackingClassifier(modelList, final_estimator=e)
    StackingRegressor()
    À utiliser quand chaque modèle ont travaillé pendant beaucoup de temps.
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split
from sklearn.linear_model import SGDClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import StackingClassifier

X, y = make_moons(n_samples=500, noise=0.3, random_state=0)
plt.scatter(X[:, 0], X[:, 1], c=y)
plt.show()

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)

model_1 = SGDClassifier(random_state=0)
model_2 = DecisionTreeClassifier(random_state=0)
model_3 = KNeighborsClassifier(n_neighbors=2)

model_4 = StackingClassifier([("SGD", model_1), 
                            ("Tree", model_2), 
                            ("KNN", model_3)],
                            final_estimator=KNeighborsClassifier())

for model in (model_1, model_2, model_3, model_4):
    model.fit(X_train, y_train)
    print(model.__class__.__name__, model.score(X_test, y_test)) # affiche le nom du modèle et son score
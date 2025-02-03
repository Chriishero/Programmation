"""
Il peut être utile de créer ses propres métriques de validations quand notre client attend un modèle qui respecte des conditions précisent, 
comme avoir de prédictions dans une zones de tolérances de +/- 20%.

custom_score = make_scorer(function, greater_is_better) : geater_is_better (True ou False) définit si le score est bon quand il est petit ou grand.
cross_val_score(model, X, y, cv=n, scoring=custom_score)
GridSearchCV(model, param_grid=params, cv=n, scoring=custom_score)
"""


import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVR
from sklearn.metrics import make_scorer # permet de créer ses propres métriques de validation
from sklearn.model_selection import cross_val_score, GridSearchCV

m = 100
X = np.linspace(0, 4, m).reshape((m, 1))
y = 2 + X**1.3 + np.random.randn(m, 1)
y = y.ravel()

def custom_metric(y, y_pred):
    return np.sum((y_pred < y + y+0.2) & (y_pred > y - y*0.2)) / y.size # retourne le nombre de prédictions qui ont une marge d'erreur de +/- 20%

custom_score= make_scorer(custom_metric, greater_is_better=True)

model = SVR(kernel='rbf', degree=3)
params = {'gamma': np.arange(0.1, 1, 0.05)}
grid = GridSearchCV(model, param_grid=params, cv=3, scoring=custom_score)
grid.fit(X, y)
best_model = grid.best_estimator_
y_pred = best_model.predict(X)

print("Score : ", custom_metric(y, y_pred))

plt.figure(figsize=(12,8))
plt.scatter(X, y)
plt.plot(X, y_pred, c='r', lw=3)
plt.plot(X, y + 0.2, c='g', ls='--')
plt.plot(X, y - 0.2, c='g', ls='--')
plt.show()


"""
Sélectionne un estimateur et précise les hyperparamètres pour améliorer le score de la prédiction :
model = LinearRregression() : régression linéaire
model = LogisticRegression() : régression logistique
model = SVC() : Support Vector Machine
model = RandomForestClasssifier() : Random Forest

model.fit(X, y) : entraine le modèle en fonction des features (tableau numpy X) et des targets (tableau numpy y à une colonne)
model.score(X, y) : évalue le modèle en testant des prédictions
model.predict(X) : utilise le modèle
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.svm import SVR

np.random.seed(0)
m = 100 # 100 échantillons
X = np.linspace(0, 10, m).reshape(m, 1) # features
y = X + np.random.randn(m, 1) # targets

model = LinearRegression()
model.fit(X, y)
score = model.score(X, y)
print(score)
predictions = model.predict(X)

plt.figure(figsize=(12,8))
plt.subplot(2,1,1)
plt.scatter(X, y)
plt.plot(X, predictions, color='r')

y = X**2 + np.random.randn(m, 1) # targets

model = SVR(C=100) # C est a modifier pour améliorer le score de la prédiction
model.fit(X, y)
score = model.score(X, y)
print(score)
predictions = model.predict(X)

plt.subplot(2,1,2)
plt.scatter(X, y)
plt.plot(X, predictions, color='r')

plt.show()

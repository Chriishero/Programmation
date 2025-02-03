"""
Sélectionne un estimateur et précise les hyperparamètres pour améliorer le score de la prédiction :
model = LinearRregression() : régression linéaire
model = LogisticRegression() : régression logistique
model = SVC() : Support Vector Machine
model = RandomForestClasssifier() : random forest
model = KNeighborsClassifier() : classificaton

model.fit(X, y) : entraine le modèle en fonction des features (tableau numpy X) et des targets (tableau numpy y à une colonne)
model.score(X, y) : évalue le modèle en testant des prédictions
model.predict(X) : utilise le modèle

Dans certain modèle, il est possible de calculer les probatilités des différentes targets :
model.predict_proba(features)
"""

import numpy as np
import pandas as pd
import seaborn as sns
from sklearn.neighbors import KNeighborsClassifier # classification

titanic = sns.load_dataset("titanic")
titanic = titanic[['survived', 'pclass', 'sex', 'age']]
titanic.dropna(axis=0, inplace=True) # supprime les données manquantes directement dans le dataset 'titanic', sans copie (inplace=True)
titanic['sex'].replace(['male', 'female'], [0, 1], inplace=True) # remplace les valeurs 'male' et 'female' par '0' et '1'
print(titanic.head())

y = titanic['survived'] # targets
X = titanic.drop('survived', axis=1) # mets toutes les colonnes, les features, en supprimant la colonne (axis=1) 'survived'

model = KNeighborsClassifier(n_neighbors=1) # (1 - 10) pour améliorer le score
model.fit(X, y)
print(model.score(X, y))

def survie(model, pclass=3, sex=0, age=17):
    x = np.array([pclass, sex, age]).reshape(1, 3) # instancie un tableau numpy avec NOS données avec lequels on veut connaître le résultat (target)
    # reshape(1, 3) : redimensionne le tableau avec 1 ligne et 3 colonnes
    print(model.predict(x))
    print(model.predict_proba(x)) # calcule les probabilités de mort (0) et de survie (1)

survie(model)
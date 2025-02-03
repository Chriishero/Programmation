"""
cv = LeaveOneOut() : permet d'évaluer le modèle sur une seule valeur à la fois
KFold : permet de diviser le dataset pour l'entrainer et l'évaluer sur différentes portions. Le désavantage est s'il y a des classes déséquilibré
dans le dataset. C'est très utile pour les régressions

ShuffleSplit : retire une proportion de données aléatoire à entrainer puis valider, et recommence autant de fois que désiré.
Même désavantage que le KFold pour la classification déséquilibré.

StratifiedKFold : crée des splits dans lesquels il y aura à chaque fois une petite portion de chaque classe.

GroupKFold : utile quand les données du dataset peuvent dépendre les unes des autres. Cela va diviser chaque "groupes" en proportion égale,
puis les rassembler avec les autres pour en faire différent paquets de cross-validation

GroupShuffleSplit : même chose mais en mélangeant les groupes
"""

import numpy as np 
import matplotlib.pyplot as plt 
import seaborn as sns
import pandas as pd 
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import cross_val_score, KFold, LeaveOneOut, ShuffleSplit, StratifiedKFold, GroupKFold
from sklearn.datasets import load_iris

iris = load_iris()

X = iris.data
y = iris.target

print(X.shape)
plt.scatter(X[:, 0], X[:, 1], c=y, alpha=0.8)
#plt.show()

cv = KFold(5, shuffle=True, random_state=0) # nombre de split du dataset 
# 5 split 
# shuffle : aléatoirement a
# état aléatoire (seed)

cv = LeaveOneOut()
cv = ShuffleSplit(4, test_size=0.2) # nombre de split, proportions de test_size
cv = StratifiedKFold(4)

cv = GroupKFold(5).get_n_splits(X, y, groups=X[:, 0]) 
# GroupKFold(5) : 5 splits (entrainement)
# get_n_splits : sépare les différents groupes du datasets, ici en fonction de la colonne 0 de 'X'

score = cross_val_score(KNeighborsClassifier() ,X, y, cv=cv) # cross validation
print(score)

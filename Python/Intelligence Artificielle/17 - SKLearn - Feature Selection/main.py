"""
Transformer : 
    Variation : 
        VarianceThreshold(threshold=n) : élimine les variables dont la variance est inférieur à un certain seuil 'n'.
    Test Statistique : 
        SelectKBest(score_funk, k=K) : sélectionne les 'K' variables X dont le score du test de dépendance 'score_funk' avec y est le plus élevé
        SelectPercentile([]) : sélectionne toutes les variables qui sont au dessus d'un certain poucentage de score
    Estimateur coefs : pré-entraine un estimateur et examine ses coefficients pour voir quelles sont les features importantes
        SelectFromModel(estimator, threshold=stat)
        RFE(estimator, step=n, min_features_to_select=m, cv=cv) : élimine 'n' variables les moins importantes de façon récursive en en gardant un minimum de 'm'
        RFECV(estimator[, step, ]) : RFE en cross-validation

Tests de dépendance : 
    Classification :
        chi2(X, y) : renvoie 2 tableaux, un avec les scores de features (élevé est meilleur) et un avec les pvalues (probabilité)
        f_classif(X, y)
        mutual_info_classif(X, y)
    Régression :
        f_regression(X, y)
        mutual_info_regression(X, y)
        
selector.get_support() : renvoie un ndarray de valeur booléenne indiquant les variables qui ont été sélectionné ou non

"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.feature_selection import VarianceThreshold, SelectKBest, chi2, SelectFromModel, RFECV, RFE
from sklearn.linear_model import SGDClassifier
from sklearn.datasets import load_iris

iris = load_iris()
X = iris.data
y = iris.target

print(X.var(axis=0)) # affiche la variance des variables

selector = VarianceThreshold(threshold=0.2)
selector.fit_transform(X)
selected_features = np.array(iris.feature_names)[selector.get_support()] # mets sous forme de ndarray, les variables qui ont été sélectionné
print(selected_features)

print(chi2(X, y))
selector = SelectKBest(chi2, k=2) # renvoie les 2 features qui ont le meilleur score
selector.fit_transform(X, y) # il faut passer les features et les targets
print(selector.get_support())

selector = SelectFromModel(SGDClassifier(random_state=0), threshold='mean') # sélectionne si les features sont au dessus de la moyenne
selector.fit_transform(X, y)
print(selector.get_support())
print(selector.estimator_.coef_) # affiche les coefficients développés par SGDClassifier
# matrice de dimension (3, 4) car c'est ce qu'il faut pour passer d'une matrice (150, 4) (features) à (150, 1) (targets avec 3 classes) 
print(selector.estimator_.coef_.mean(axis=0)) # moyenne utilisé de chaque variable
print(selector.estimator_.coef_.mean(axis=0).mean()) # les variables sélectionné ont une moyenne (au dessus) supérieur à celle-ci
# moyenne de toutes les lignes pour chaque colonne (axis=1), puis moyenne des colonnes

selector = RFECV(SGDClassifier(random_state=0), step=1, min_features_to_select=2, cv=5) # renvoie les 2 features qui ont le meilleur score
selector.fit(X, y) # il faut passer les features et les targets
print(selector.ranking_) # renvoie le classement des variables par ordre d'importance
print(selector.cv_results_) # renvoie le score de chaque itération

plt.figure(figsize=(10,6))
plt.plot(X)
plt.legend(iris.feature_names)
plt.show()
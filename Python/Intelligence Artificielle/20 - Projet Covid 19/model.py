"""
1. Mettre les données dans un format propice au ML
    - Train / Test
    - Encodage
    - Nettoyage des NaN

Underfitting? :
    - PolynomialFeatures
    - Feature Engineering
    - Modèle plus complexe

Overfitting? :
    - Imputation / fillna
    - SelectFromModel
    - Régularisation

F1 : la précision et la sensibilité (recall) sont des métriques permettant de mesurer la proportion de faux positif (erreur type 1) et de faux négatif (2)
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from sklearn.model_selection import train_test_split, GridSearchCV, RandomizedSearchCV
# RandomizedSearchCV : cherche de façon aléatoire différente combinaison dans tout le domaine des hyper-paramètres
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier
from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
from sklearn.pipeline import make_pipeline
from sklearn.feature_selection import SelectKBest, f_classif
# SelectKBest : utilise un test statistique pour faire une sélection de variable
# f_classif : test ANOVA
from sklearn.preprocessing import PolynomialFeatures, StandardScaler
from sklearn.decomposition import PCA
from sklearn.metrics import f1_score, confusion_matrix, classification_report, precision_recall_curve, recall_score
# f1_score : rapport précision/sensibilité
# confusion_matrix : mesure la précision et la sensibilité
# classification_report : permet un bilan du recall, de la précision, du score f1, etc
# precision_recall_curve : visualise la futures précisions/sensibilité du modèle en fonction d'un seuil de prédiction
from sklearn.model_selection import learning_curve # permettra de savoir si le modèle est en overfitting ou underfitting
from preprocessing import X_train, X_test, y_train, y_test

# Procédure d'évaluation
def evaluation(model):
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    print(confusion_matrix(y_test, y_pred))
    print(classification_report(y_test, y_pred))

    N, train_score, val_score = learning_curve(model, X_train, y_train, cv=4, scoring='f1', train_sizes=np.linspace(0.1, 1, 10))
    # np.linspace(0.1, 1, 10) : 0.1 à 1 avec 10 découpes

    plt.figure(figsize=(12,8))
    plt.plot(N, train_score.mean(axis=1), label='train score') # évolution de 'N' (nombre d'échantillon pour entrainer le modèle) et la moyenne du 'train_score'
    plt.plot(N, val_score.mean(axis=1), label='val score')
    plt.legend()
    # on peut voir que le modèle est en overfitting (manque de donnée), car le train_score est bon, mais le val_score mauvais

preprocessor = make_pipeline(PolynomialFeatures(2, include_bias=False), SelectKBest(f_classif, k=10)) # sélectionne les 10 meilleurs variables selon le test ANOVA
RandomForest = make_pipeline(preprocessor, RandomForestClassifier(random_state=0))
AdaBoost = make_pipeline(preprocessor, AdaBoostClassifier(random_state=0))
SVM = make_pipeline(preprocessor, StandardScaler(), SVC(random_state=0)) # les SVM nécessite de la normalisation
KNN = make_pipeline(preprocessor, StandardScaler(), KNeighborsClassifier())

models_dict = {"RandomForest": RandomForest, "AdaBoost": AdaBoost, "SVM":SVM, "KNN":KNN}

"""for name, model in models_dict.items():
    print(name)
    evaluation(model)
"""

hyper_params = {"svc__gamma":[1e-3, 1e-4], 
                "svc__C":[1, 10, 100, 1000], 
                "pipeline__polynomialfeatures__degree": [2,3,4],
                "pipeline__selectkbest__k": range(40, 60)} # prend les hyperparamètres de l'étape 'svc'
# Un 'GridSearchCV' serait beaucoup trop long

grid = RandomizedSearchCV(SVM, hyper_params, scoring='recall', cv=4, n_iter=40, random_state=0) 
# le recall renvoie le nombre de personne qui sont positif mais qu'on ne détecte pas
# RandomizedSearchCV : cherche de façon aléatoire différente combinaison dans tout le domaine des hyper-paramètres

grid.fit(X_train, y_train)
print("Best params : ", grid.best_params_)

evaluation(grid.best_estimator_) # le modèle n'est pas en overfitting

precision, recall, threshold = precision_recall_curve(y_test, grid.best_estimator_.decision_function(X_test))
plt.figure(figsize=(12,8))
plt.plot(threshold, precision[:-1], label='precision')
plt.plot(threshold, recall[:-1], label='sensibilité')
plt.legend()

def model_final(model, X, threshold=0):
    return model.decision_function(X) > threshold

#plt.show()

y_pred = model_final(grid.best_estimator_, X_test, threshold=-1)
print("F1 : ", f1_score(y_test, y_pred)) # évalue le score f1 de la prédiction
print("Recall : ", recall_score(y_test, y_pred))
"""
Un dataset est toujours divisé en 2 parties, un train-set (80%) qui permet d'entrainer le modèle, et un test-set (20%) qui permet de l'évaluer
Overfitting : Le modèle s'est trop perfectionné sur le Trainset et a perdu tout sens de généralisation, les érreurs sur le Train diminuent, mais celles sur le Test augmentent

Learning Curve : les courbes d'apprentissages montrent l'évolution des performances du modèle en fonction du nombre de donnée qu'on lui fournit
learning_curve(model, X_train, y_train, train_sizes=np.linspace(0.2, 1.0, 5), cv=5) : train_sizes, quantité de données à utiliser, ici 20 à 100% en lots de 5 (20-40-60-80-100)

Méthode manuelle de tester différent valeur pour une seul hyperparamètre du modèle pour trouver le meilleur :
val_score = []
for k in range(1, 50):
    score = cross_val_score(KNeighborsClassifier(1), X_train, y_train, cv=5).mean()
    val_score.append(score) 

Méthode avec fonction SKLearn :
train_score, val_score = validation_curve(model, X_train, y_train, param_name='n_neighbors', param_range=k, cv=5)
"n_neighbors" : hyperparamètre à régler
k : itérateur représentant les valeurs à tester pour l'hyperparamètre
cv : nombre de découpe dans le cross validation

Grid = GridSearchCV(model, param_grid, cv) : Construit une grille de modèles avec toutes les combinaisons d'hyperparamètres présents dans le param_grid
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split, cross_val_score, validation_curve, GridSearchCV, learning_curve
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import confusion_matrix

iris = load_iris()
X = iris.data
y = iris.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=5) # divise le dataset / test_size : 20% / random_state=seed

plt.figure(figsize=(10,4))
plt.subplot(121)
plt.scatter(X_train[:, 0], X_train[:, 1], c=y_train, alpha=0.8)
plt.title("Train set")
plt.subplot(122)
plt.scatter(X_test[:, 0], X_test[:, 1], c=y_test, alpha=0.8)
plt.title("Test set")

model = KNeighborsClassifier() # crée un modèle de 'KNeighborsClassifier' avec comme hyperparamètre 'n_neighbors' (nombre de voisin)

k = np.arange(1, 50)
train_score, val_score = validation_curve(model, X_train, y_train, param_name='n_neighbors', param_range=k, cv=5)
# divise le dataset en 5 parties pour l'évaluation de différentes valeurs 'k' pour l'hyperparamètre "n_neighbors" du modèle

plt.figure()
plt.plot(k, val_score.mean(axis=1), label='validation') # affiche l'hyperparamètre en fonction du validation score
plt.plot(k, train_score.mean(axis=1), label='train')
plt.ylabel("score")
plt.xlabel("n_neighbors")
plt.legend()

param_grid = {"n_neighbors": np.arange(1, 20), 'metric': ['euclidean', "manhattan"]} # dictionnaire des différents hyperparamètre à réglé ainsi que leurs valeurs à tester
grid = GridSearchCV(model, param_grid=param_grid, cv=5)
grid.fit(X_train, y_train)

print("Meilleur score : ", grid.best_score_)
print("Meilleurs paramètres : ", grid.best_params_)

model = grid.best_estimator_ # sauvegarde le modèle
print("Score Test : ", model.score(X_test, y_test))

print(confusion_matrix(y_test, model.predict(X_test))) # 'confusion_matrix' permet de montrer les erreurs de classement

N, train_score, val_score = learning_curve(model, X_train, y_train, train_sizes=np.linspace(0.1, 1.0, 10), cv=5) # train_sizes : quantité de données à utiliser (10% à 100% en lots de 10)
# N contient les différentes quantités de données

plt.figure()
plt.plot(N, train_score.mean(axis=1), label='train')
plt.plot(N, val_score.mean(axis=1), label="validation")
plt.xlabel("train_sizes")
plt.legend()
plt.show()
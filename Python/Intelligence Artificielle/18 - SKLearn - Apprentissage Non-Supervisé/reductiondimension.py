"""
Apprentissage Non-Supervisé : la machine analyse la structure des données X pour apprendre elle-même à réaliser certains tâches.

Clustering : regroupe les données selon leurs ressemblances, classification non-supervisé
Détection d'anomalies : trouve les échantillons dont les caractéristiques (X) sont très éloignés de celles des autres échantillons.
Réduction de la dimension : en étudiant la structure de nos données, la machine apprend à la simplifier tout en conservant les principales informations.
    PCA : projete les données sur des axes appelés Composantes Principales, en cherchant à minimiser la distance entre nos points et leur projections.
        Hyper-Paramètres :
            n_components : nombre de composantes sur lesquels projeter les données (2D : 2 | 3D : 3 | 0.95 : 95% de la variance)
        Méthodes : 
            fit_transform(X) : transform les données
            inverse_transform(Xtransform) : décompresse les données pour leurs faire retrouver leur nombre de composantes originelles, sans les remettre à leur position d'origine
        Attributs :
            components_ : renvoie le contenue de chaque composantes
            explained_variance_ratio_ : indique le pourcentage de variance préservé par chaque composante
            n_components_ : indique le nombre de composants préservés
        Il faut toujours standardiser les données avant d'utiliser PCA (StandardScaler).
        PCA est normalement conçu pour traiter les variables continues.
        PCA n'est pas efficace sur les datasets non-linéaires.
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn.datasets import load_digits

digits = load_digits()
images = digits.images
X = digits.data # tableau (1797, 64)
y = digits.target

model = PCA(n_components=2)
X_reduced = model.fit_transform(X) # tableau (1797, 2)

plt.scatter(X_reduced[:, 0], X_reduced[:, 1], c=y)
plt.colorbar()
plt.show()

model = PCA(n_components=64)
X_reduced = model.fit_transform(X) # tableau (1797, 2)
plt.plot(np.cumsum(model.explained_variance_ratio_))
plt.show()

n_components = np.argmax(np.cumsum(model.explained_variance_ratio_) > 0.99) # inidique à partir de combien de composantes on atteint les 99% de variance
print(n_components)
model = PCA(n_components=n_components)
#model = PCA(n_components=0.95) # conserve 95% de la variance

X_reduced = model.fit_transform(X) # tableau (1797, 2)
X_recovered = model.inverse_transform(X_reduced)
plt.imshow(X_recovered[0].reshape((8, 8))) # redimensionne l'image en 8x8 pixels
plt.title(y[0])
plt.show()
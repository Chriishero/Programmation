"""
Apprentissage Non-Supervisé : la machine analyse la structure des données X pour apprendre elle-même à réaliser certains tâches.

Clustering : regroupe les données selon leurs ressemblances, classification non-supervisé
    KMeans : cherche la position des centres qui minimise la distance entre les points d'un cluser et le centre de ce dernier.
        Hyper-Paramètres : 
            n_clusters : nombre K de clusters
            n_init : nombre d'exécutions (10)
            max_iter : nombre d'itérations (300)
            Init : type d'initialisation (K-means++)
        Méthodes : 
            fit(X) : éxecute l'algorithme K-Mean
            predict(X) : centroid le plus proche de X
            score(X) : calcul l'intertia (négatif)
        Attributs :
            clusters_centersç : position des centroids
            labels_ : équivalent de Predict(Xtrain)
            intertia : calcul de l'inertia (positif)
    DBSCAN() : sur des clusers non convexes et anisotropes
    AgglomerativeClustering() : sur des clusers non convexes et anisotropes

Détection d'anomalies : trouve les échantillons dont les caractéristiques (X) sont très éloignés de celles des autres échantillons.
Réduction de la dimension : en étudiant la structure de nos données, la mahcine apprend à la simplifier tout en conservant les principales informations.
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.datasets import make_blobs


X, y = make_blobs(n_samples=100, centers=3, cluster_std=1.2, random_state=1)

inertia = []
K_range = range(1, 20) # rangé de valeur à tester
for k in K_range: # permet de tester différent nombre de cluster pour trouver le meilleur
    model = KMeans(n_clusters=k).fit(X)
    inertia.append(model.inertia_)

plt.plot(K_range, inertia)
plt.xlabel("Nombre de clusters")
plt.ylabel("Cout du model (intertia)")
plt.show()

model = KMeans(n_clusters=3).fit(X)
plt.scatter(X[:, 0], X[:, 1], c=model.predict(X))
plt.scatter(model.cluster_centers_[:,0], model.cluster_centers_[:, 1], c='r')
plt.show()
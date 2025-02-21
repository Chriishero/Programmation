"""
Toutes les opérations d'objet sont possible sur un axe spécifique
A.sum() : fais la somme de tous les éléments 
A.sum(axis=0) : fais la sommme de tous les éléments qui se suivent verticalement
A.sum(axis=1) : fais la sommme de tous les éléments qui se suivent horizontalement
A.cumsum() : fais la somme cumulé de tous les éléments

A.prod() : produit de tous les éléments
A.cumprod() : produit cumulé

A.min() : renvoie l'élément minimum du tableau
A.min(axis=0) : le minimum selon l'axe vertical de chaque colonne
A.argmin() : renvoie la position du minimum

A.sort() : trie tous les éléments
A.argsort() : renvoie l'index des éléménts dans l'ordre du tri dans modifier le tableau

A.mean() : moyenne du tableau
A.std() : écart type du tableau
A.var() : variance du tableau

Statistiques :
NaN : Not a Number
np.corrcoef(A) : trace une matrice de corrélation pour le tableau A entre chaque chaque ligne
np.unique(A,) : renvoie les entités présentent dans le tableau, ainsi que leur nombre de répétition

np.nan : renvoie un 'NaN'
np.isnan(A) : renvoie un tableau de booléen (masque) qui vérifie la condition si une valeur est un 'NaN'
np.nanmean(A) : calcule la moyenne en ignorant les entités 'NaN'
np.nanstd(A) : calcule l'écart type en ignorant les entités 'NaN'
np.nanvar(A) : calcule la variance en ignorant les entités 'NaN'

Algèbre Linéaire :
A.dot(B) : produit matricielle entre 'A' et 'B'
np.linalg.det(A) : calcule le déterminant de la matrice 'A'
np.linalg.inv(A) : retourne l'inverse de tous les éléments
np.linalg.pinv(A) : retourne l'inverse d'une matrice avec des combinaisons linéaire entre lignes et colonnes
np.linalg.eig(A) : renvoie les valeurs propres et les vecteurs propres de la matrice
"""

import numpy as np

np.random.seed(0)
A  = np.random.randint(0, 10, [5, 5])
print(A.sum())

B = np.corrcoef(A)[0, 1] # corrélation de la première ligne à le première colonne
print(B)

values, counts = np.unique(A, return_counts=True) # renvoie les entités présentent dans le tableau, ainsi que leur nombre de répétition
print(values[counts.argsort()]) # trie 'values' selon l'ordre des indexes des valeurs la moins répétés à la plus

for i, j in zip(values[counts.argsort()], counts[counts.argsort()]): # affiche toutes les valeurs selon leur fréquence d'apparition
    # pour i et j, itérer les 'values' selon leur fréquence d'apparition, et de la fréquence d'appatition 'counts'
    print(f"{i} apparait {j} fois")

C = np.random.randn(5,5)
C[3,3] = np.nan
C[1,0] = np.nan
print(np.isnan(C).sum()) # renvoie le nombre de 'NaN' dans le tableau
print(np.isnan(C).sum()/C.size) # renvoie le pourcentage de 'NaN'

C[np.isnan(C)] = 0 # pour tous les éléments qui sont des 'NaN', ils seront égale à 0
print(C)

a = np.ones((2, 3))
b = np.ones((3, 2))
print(a)
print(b)
print(a.dot(b)) # renvoie le produit matricielle des tableaux 'a' et 'b'
print(b.dot(a)) # renvoie le produit matricielle des tableaux 'b' et 'a'

c = np.random.randint(0, 10, [3,3])
print(np.linalg.det(c)) # renvoie déterminant de la matrice
print(np.linalg.inv(c)) # inverse tous les éléments de la matrice
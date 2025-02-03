"""
Les 2 attributs les plus important des tableaux Numpy (ndarray) en machine learning sont '.shape' et '.size'.

shape : renvoie le nombre de ligne, colonne et dimension sous forme de tuple
size : renvoie le produit entre le nombre de ligne, colonne et dimension

np.array([1,2,3]) : # instancie un tableau de une dimension de 3 éléments
np.zeros((l, c, d)) : instancie un tableau remplie de 0
np.ones((l, c, d)) : instancie un tableau remplie de 1
np.full((l, c, d), n) : instancie un tableau remplie de 'n'
np.eye(n) : instancie une matrice identité, avec 'n' nombre en diagonal

np.random.randn(l, c, d) : instancie un tableau remplie de nombre aléatoire
np.random.seed(n) : créer une graine 'n' qui fait en sorte que la génération soit toujours la même, sous cette 'seed'

np.linspace(x, y, n) : instancie un tableau de 'n' valeur répartie entre 'x' et 'y' dans l'ordre croissant
np.arange(x, y, n) : instancie un tableau de valeur répartie entre 'x' et 'y', dont le pas est de 'n'

Dans n'importe quel constructeur, le paramètres 'dtype' sont disponible : 
dtype=np.float16 : les valeurs instanciées seront de type float et occuperont 16 bits dans la mémoire (rapide et peu précis)
dtype=np.float64 : les valeurs instanciées seront de type float et occuperont 64 bits dans la mémoire (lent et précis)

Manipulation : 
np.hstack((A, B)) : cole les tableaux 'A' et 'B' horizontalement
np.vstack((A, B)) : cole les tableaux 'A' et 'B' verticalement
np.concatenate((A, B), axis=0) : cole les tableaux 'A' et 'B' verticalement
np.concatenate((A, B), axis=1) : cole les tableaux 'A' et 'B' horizontalement
np.concatenate((A, B), axis=2) : cole les tableaux 'A' et 'B' en profondeur

A.reshape((x,y)) : remanipule la forme du tableau 'A', pour lui donner une forme x,y, à condition que le nombre d'élément sera la même entre la forme initiale et finale
A.squeeze() : fait disparaitre les dimensions du tableau 'A' qui sont égale(s) à 1
A.ravel() : aplatit le tableau 'A', un tableau de dimension (4,3) deviendra de dimension (12,)
"""

import numpy as np

D = np.linspace(0, 10, 20) # créer un tableau de 20 valeurs répartie entre 0 et 10
print(D)

E = np.arange(0, 10, 1) # créer un tableau de valeur répartie entre 0 et 10, dont le pas est de 1
print(E)

B = np.zeros((3,2)) # créer un tableau remplie de 0 de dimension : 3 lignes, 2 colonnes, 1 dimension
print(B)

np.random.seed(0) # chaque génération aléatoire sera la même
C = np.random.randn(3,2) # créer un tableau remplie de nombre aléatoire de dimension : 3 lignes, 2 colonnes, 1 dimension
print(C)

X = np.concatenate((B, C), axis=1) # cole les tableaux 'B' et 'C' horizontalement
print(X.shape)


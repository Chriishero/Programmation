"""
A[0, 1] : accède à l'élément de la ligne 1 de la colonne 2
A[0, 1, 1] : accède à l'élément de la ligne 1 de la colonne 2 et de la dimension 2
A[:, 0] : accède à tout les éléments de la 1er colonne
A[0, :] : accède à tout les éléments de la 1er ligne
A[0] : idem
A[0:2, 0:2] : accède aux 2 premières ligne et aux 2 premières colonnes
A[::2, ::2] : toutes les valeurs en faisant des pas de 2

A < 5 : renvoie un tableau remplie de booléen
A[A < 5] : renvoie tous les éléments inférieur à 5
"""

import numpy as np

A = np.array([[1,2,3], [4,5,6], [7,8,9]])
B = A[0:2, 0:2] # subsetting : créer un plus petit tableau à partir du premier (2 premières lignes des 2 premières colonnes)
print(B)

A[0:2, 0:2] = 10 # transforme tous les éléments en '10'
print(A)
print(A[:, -2:]) # accède à toutes les lignes, aux 2 dernières colonnes

C = np.zeros((4,4))
C[1:-1, 1:-1] = 1 # remplace les colonnes 2 et 3 des lignes 2 et 3 par des 1
print(C)

D = np.zeros((5,5))
D[::2, ::2] = 1 # toutes les valeurs en sautant un pas de deux, lignes et colonnes, sont remplacé par des 1
print(D)

E = np.random.randint(0, 10, [5,5]) # créer un tableau remplie de nombre aléatoire entre 0 et 10, de dimension 5x5
print(E < 5)
E[(E < 5) & (E > 2)] = 10 # tous les éléments inférieur à 5 et supérieur à 2, deviennent des 10
print(E)


"""
On peut additionner 2 tableaux, si ils sont les mêmes dimensions.

Le Broadcasting consiste à étendre les dimensions d'un tableau.
A = (2,3)
B = (2,1)
'B' doit avoir qu'une seule colonne/ligne pour que le broadcasting fontionne
A + B = (2,3)

A = (4,1)
B = (1,3)
A + B = (4,3)

Ça fonctionne aussi si l'un des tableaux à des dimensions 'incomplètes' :
A = (4,1)
B = (3,)
Le '3' est considéré comme la dernière dimension du tableau : 
A + B = (4,3)
Il est donc impératif de vérifier les dimensions de nos tableaux et d'utiliser reshape si nécessaire.
"""

import numpy as np

A = np.ones((4,1))
B = np.random.randint(0,10, [1,3])
print(A+B)
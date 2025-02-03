"""
Morphology : technique mathématique qui permet de transformer des matrices.
On définit une structure, qui va se déplacer de pixel en pixel sur l'image, en rencontrant un pixel blanc, elle va soit imprimer des pixels (dilation) ou en effacer (érosion)

ndimage.binary_opening(matrice) : permet l'érosion et la dilation
"""

import numpy as np 
import matplotlib.pyplot as plt
from scipy import ndimage

np.random.seed(0)
X = np.zeros((32, 32)) # créer une surface vide
X[10:-10, 10:-10] = 1 # mets un carré au milieu
X[np.random.randint(0,32,30), np.random.randint(0,32,30)] = 1 # colors de pixels aléatoirement 

open_x = ndimage.binary_opening(X) # enlève les artefact

plt.imshow(open_x)
plt.show()
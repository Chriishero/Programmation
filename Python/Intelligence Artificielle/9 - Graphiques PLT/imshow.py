"""
imshow permet d'afficher n'importe quel tableau
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy import misc
from sklearn.datasets import load_iris

iris = load_iris() # charge le dataset des iris

x = iris.data # récupère les features (variables)
y = iris.target # récupère la target
name = list(iris.target_names)

print(f"x contient {x.shape[0]} exemples et {x.shape[1]} variables")
print(f"il y a {np.unique(y).size} classes")

plt.imshow(np.corrcoef(x.T))
# corrcoef : renvoie une matrice de corrélation pour le tableau 'x'
plt.show()

face = misc.face(gray=True)
plt.imshow(face) # affiche l'image 'face'
plt.show()

f = lambda x, y: np.sin(x) + np.cos(x+y)
X = np.linspace(0, 5, 100) # crée un vecteur ndarray
Y = np.linspace(0, 5, 100)
X, Y = np.meshgrid(X, Y) # crée une grille à partir des axes 'X' et 'Y'

Z = f(X, Y)
plt.imshow(Z) # matrice 'Z' de dimensions 100 lignes et 100 colonnes
plt.show()
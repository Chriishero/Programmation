"""
La POO est obligatoire pour faire des graphiques en 3D
"""

from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris

iris = load_iris() # charge le dataset des iris

x = iris.data # récupère les features (variables)
y = iris.target # récupère la target
name = list(iris.target_names)

print(f"x contient {x.shape[0]} exemples et {x.shape[1]} variables")
print(f"il y a {np.unique(y).size} classes")

ax = plt.axes(projection='3d') # crée un objet ax, en 3D
ax.scatter(x[:,0], x[:,1], x[:,2], c=y) # 'c=y' couleur différente en fonction de la classe d'iris
plt.show()

f = lambda x, y: np.sin(x) + np.cos(x+y)
X = np.linspace(0, 5, 100) # crée un vecteur ndarray
Y = np.linspace(0, 5, 100)
X, Y = np.meshgrid(X, Y) # crée une grille à partir des axes 'X' et 'Y'

Z = f(X, Y)

ax = plt.axes(projection='3d') # crée un objet ax, en 3D
ax.plot_surface(X, Y, Z, cmap="plasma") # affiche la fonction 'Z' de 'Y' par rapport à 'X'
plt.show()
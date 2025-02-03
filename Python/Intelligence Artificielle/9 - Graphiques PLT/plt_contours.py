"""
Graphique en 3 dimensions avec une vue du dessus.
"""
import numpy as np
import matplotlib.pyplot as plt

f = lambda x, y: np.sin(x) + np.cos(x+y)
X = np.linspace(0, 5, 100) # crée un vecteur ndarray
Y = np.linspace(0, 5, 100)
X, Y = np.meshgrid(X, Y) # crée une grille à partir des axes 'X' et 'Y'

Z = f(X, Y)

plt.contour(X, Y, Z, 20, colors="black") # affiche la fonction 'Z' de 'Y' en fonction de 'X' avec 20 niveaux
plt.show()
plt.contourf(X, Y, Z, 20, cmap='RdGy') # permet d'ajouter la colormap
plt.colorbar() # légende pour les couleurs
plt.show()
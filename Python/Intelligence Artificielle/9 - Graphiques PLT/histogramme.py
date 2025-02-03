"""
En Machine Learning, l'histogramme de voir la distribution des données avec lesquels on travaille
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris

iris = load_iris() # charge le dataset des iris

x = iris.data # récupère les features (variables)
y = iris.target # récupère la target
name = list(iris.target_names)

plt.hist(x[:,0], bins=30) # en abscisse, la longueur des sépals, en ordonnées, le nombre d'apparition de sépals d'une certaine longueur
plt.hist(x[:,1], bins=30)
# bins : nombre de section de l'histogramme
plt.show()

plt.hist2d(x[:,0], x[:,1]) # histogramme en 2d
plt.xlabel("longueur sépal")
plt.ylabel("largeur sépal")
plt.colorbar() # légende qui indique à quoi correspond les couleurs
plt.show()

from scipy import misc
import matplotlib.pyplot as plt

face = misc.face(gray=True)
plt.hist(face.ravel(), bins=255) # permet de voir la fréquence d'apparition de chaque pixel, d'où bins=255
plt.show()
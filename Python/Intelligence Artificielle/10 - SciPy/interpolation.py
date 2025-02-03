"""
Une interpolation sert à rajouter des valeurs dans un dataset, pour combler les troues des valeurs manquantes.
Il faut être certain que l'interpolation ne cache pas la réalité

Type d'interpolation :
linear
cubic
quadratic
"""

import numpy as np 
import matplotlib.pyplot as plt 
from scipy.interpolate import interp1d # génère une fonction d'interpolation


x= np.linspace(0, 10, 10)
y = np.sin(x)
plt.scatter(x, y)

f = interp1d(x, y, kind='cubic')
new_x = np.linspace(0, 10, 30)
result = f(new_x) # tableau qui contient les points 30 points (new_x) interpolé au tableau 'x'

plt.scatter(x, y)
plt.scatter(new_x, result, c="red")
plt.show()


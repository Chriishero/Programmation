"""
------Tracer des Graphiques en utilisant les Classes------

fig, ax = plt.subplots() : crée un objet 'fig', et un tableau ndarray 'ax' qui contient des objets
ax.plot(x,y)

fig, ax = plt.subplots(2, 1, sharex=True) : crée différent 'subplots' qui partagent la même abscisse, 2 lignes et 1 colonne
ax[0].plot(x, y)
ax[1].plot(x, y)
"""
import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0,2,10) # tableau de 10 points allant de 0 à 2
y = x**2

fig, ax = plt.subplots(2,1, sharex=True) # crée un objet 'fig', et un tableau ndarray 'ax' qui contient des objets
ax[0].plot(x, y) # trace la courbe de 'y' en fonction de 'x'
ax[1].plot(x, np.sin(x))
plt.show()
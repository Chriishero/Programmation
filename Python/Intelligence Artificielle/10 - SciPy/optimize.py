"""
optimize.curve_fit : trouve les bons paramètres d'un modèle 'f' avec les moindres carrés
optimize.minimize : permet de trouver de converger vers le premier minimum de 'f' qu'elle rencontre à partir d'un
                    point de départ 'x0'
"""

import numpy as np 
import matplotlib.pyplot as plt
from scipy import optimize

x = np.linspace(0, 2, 100)
y = 1/3*x**3 - 3/5 * x**2 + 2 + np.random.randn(x.shape[0])/20

def f(x, a, b, c, d):
    return a * x**3 + b * x**2 + c * x + d 

params, param_cov = optimize.curve_fit(f, x, y) # renvoie 2 tableaux, un avec les paramètres de la fonction 'f', ainsi que ses covariances

plt.scatter(x,y)
plt.plot(x, f(x, params[0], params[1], params[2], params[3]), c="red")
plt.show()

def f(x):
    return x**2 + 15*np.sin(x)

x = np.linspace(-10, 10, 100)

x0 = -5
result = optimize.minimize(f, x0=x0).x # à partir du point 'x0', converge vers le minimum de la fonction 'f'

plt.plot(x, f(x), lw=3)
plt.scatter(result, f(result), s=100, c='r') # affiche le point sur le minimum 'result'
plt.scatter(x0, f(x0), s=200, marker="+", c='g') # affiche le point de départ, en affichant un '+'
plt.show()

def f(x):
    return np.sin(x[0]) + np.cos(x[0]+x[1]) * np.cos(x[0])

x = np.linspace(-3, 3, 100) # crée un vecteur ndarray
y = np.linspace(-3, 3, 100)
x, y = np.meshgrid(x, y) # crée une grille à partir des axes 'x' et 'y'

x0 = np.zeros((2, 1))
x0 = x0.ravel() # applatit 'x0' car il doit avoir une seule dimension pour 'optimize.minimize' 
result = optimize.minimize(f, x0=x0).x

plt.contour(x, y, f(np.array([x, y])), 20) # affiche la fonction 'f' de 'y' en fonction de 'x' avec 20 niveaux
plt.scatter(x0[0], x0[1], marker="+", c="r", s=100) # affiche le point 'x0' au coordonnées 'x0[0]' et 'x0[1]'
plt.scatter(result[0], result[1], c="g", s=100)
plt.show()
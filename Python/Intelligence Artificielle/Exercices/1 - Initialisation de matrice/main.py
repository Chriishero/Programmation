import numpy as np 

def initialisation(m, n):
    matrice = np.random.randn(m, n)
    matrice = np.concatenate((matrice, np.ones((matrice.shape[0], 1))), axis=1)
    return matrice

print(initialisation(3,4))
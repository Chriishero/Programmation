import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression

n_features = 5
n_samples = 500

x, y = make_regression(n_samples=n_samples, n_features=n_features, noise=10, random_state=0)

y = y.reshape((y.shape[0], 1))
X = np.hstack((x, np.ones((x.shape[0], 1))))

def weight_function(X, x, tau):
    x = x.reshape(1, -1)
    # x : (6,)
    # x.reshape(1, -1) : (1, 6)
    return np.exp(-np.sum((X - x)**2, axis=1) / 2*np.square(tau))

def locally_weighted_regression(X, x, y, tau):
    W = np.diag(weight_function(X, x, tau)) # créer une matrice diagonal de tous les poids w
    theta = np.linalg.inv(X.T @ W @ X) @ X.T @ W @ y # @ = np.dot()

    return x.dot(theta)

x = np.hstack((np.random.randn(1, n_features), np.ones((1, 1)))) 
prediction = locally_weighted_regression(X=X, x=x, y=y, tau=1) # prédiciton de y en fonction de x
print(prediction)

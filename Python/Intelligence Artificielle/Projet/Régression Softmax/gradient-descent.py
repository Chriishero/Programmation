import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification

n_samples = 500
n_features = 10
n_classes = 4

x, y = make_classification(n_samples=n_samples, n_features=n_features, n_classes=4, n_informative=2, n_clusters_per_class=1, random_state=0)
X = np.hstack((x, np.ones((x.shape[0], 1))))
#y = y.reshape((y.shape[0], 1))

theta = np.random.randn(n_features+1, n_classes)

print(X.shape)
print(theta.shape)
print(y.shape)

def model(X, theta):
    return X.dot(theta)

def cross_entropy(X, theta):
    predicted_probability = np.exp(model(X, theta)) / np.sum(np.exp(model(X, theta)), axis=1, keepdims=True) 
    # keepdims préserve les dimensions de la matrice après une opération comme sum, mean, etc
    # (n_samples, 1) au lieu de (n_samples,)

    # Probabilité prédite pour la classe correspondante à chaque échantillons x
    true_probatility = predicted_probability[range(len(y)), y]
    
    return -np.log(true_probatility)

print(cross_entropy(X, theta))
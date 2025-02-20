import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification

n_samples = 500
n_features = 10
n_classes = 4

x, y = make_classification(n_samples=n_samples, n_features=n_features, n_classes=4, n_informative=2, n_clusters_per_class=1, random_state=0)
X = np.hstack((x, np.ones((x.shape[0], 1))))
y = y.reshape((y.shape[0], 1))

theta = np.random.randn(n_features+1, n_classes)

def model(X, theta):
    return X.dot(theta)

def cross_entropy(X, theta):
    denominateur = []
    entropy = []
    for i in range(n_classes):
        denominateur.append(np.exp(model(X, theta[:, i])))

    for i in range(n_classes):
        entropy.append(np.exp(model(X, theta[:, i])) / np.sum(denominateur))
    
    return np.sum( -np.log(np.sum(entropy)))

print(cross_entropy(X, theta))
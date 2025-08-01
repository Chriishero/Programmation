import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification

X, y = make_classification(n_samples=500, n_features=10, n_informative=8, n_classes=4, random_state=0)
y = y.reshape((y.shape[0], 1))

class GDAClassifier:
    def __init__(self):
        self.phi = None
        self.mu = None
        self.sigma = None

    def prior_probability(self, y):
        m = len(y)
        classes, counts = np.unique(y, return_counts=True)
        return 1/m * counts
    
    def means(self, X, y):
        classes = np.unique(y)
        #return np.array([X[y.flatten() == c].mean(axis=0) for c in classes])
        return np.array([X[y.flatten() == c].sum(axis=0) / (y.flatten() == c).sum(axis=0)  for c in classes]) # ou X[y.flatten() == c].mean(axis=0)
    
    def covariance_matrix(self, X, y):
        classes = np.unique(y) 
        mu = self.means(X, y)
        #return np.array([X[y.flatten() == c].var(axis=0) for c in classes])
        return np.array([ 
            ((X[y.flatten() == c] - mu[i])**2).sum(axis=0) / (X[y.flatten() == c].shape[0]) for i, c in enumerate(classes)
        ])
    
    def bayes_rule(self, X):
        sigma = self.sigma
        mu = self.mu
        phi = self.phi # P(y)

        # P(y|X) = P(X|y) * P(y) / P(X)
        return np.log(phi) - 1/2 * np.sum(((X[:, np.newaxis, :] - mu)**2) / sigma**2, axis=2) # log(P(X|y))
        # np.newaxis : ajoute une dimension supplémentaire, qui sera comparé aux moyennes mu des classes

    def fit(self, X, y):
        self.phi = self.prior_probability(y)
        self.mu = self.means(X, y)
        self.sigma = self.covariance_matrix(X, y)

    def predict(self, X):
        return np.argmax(self.bayes_rule(X), axis=1) # renvoie la classe de y qui maximise P(y|X)
    
model = GDAClassifier()
model.fit(X, y)
y_pred = model.predict(X)

from sklearn.metrics import accuracy_score
print("Accuracy:", accuracy_score(y, y_pred))
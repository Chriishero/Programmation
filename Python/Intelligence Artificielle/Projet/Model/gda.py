import numpy as np

class GDA:
    def __init__(self):
        self.phi, self.mu, self.sigma = None, None, None

    def _prior_probability(self, y):
        m = len(y)
        return 1/m * np.sum(y)
    
    def _means_function(self, X, y):
        m, n = X.shape
        classes = np.unique(y)
        return np.array([np.sum(X[c == y]) / np.sum(np.ones_like(X)[c == y]) for c in classes])
    
    def _covariance_matrix(self, X, y):
        m, n = X.shape
        cov = np.zeros((2, 2))
        cov[0, 0] = 1/m * np.sum((X - np.mean(X))**2)
        cov[0, 1] = 1/m * np.sum((np.sum(X) - np.mean(X)) * (np.sum(y) - np.mean(y)))
        cov[1, 0] = cov[0, 1]
        cov[1, 1] = 1/m * np.sum((y - np.mean(y))**2)
        return cov

from sklearn.datasets import make_classification
X, y = make_classification(n_samples=500, n_features=10, n_informative=8, n_classes=2, random_state=0)

model = GDA()
print(model._means_function(X, y))
print(model._covariance_matrix(X, y))
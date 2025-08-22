import numpy as np

class GDAClassifier:
    def __init__(self):
        self.phi = None
        self.mu = None
        self.sigma = None

    def _prior_probability(self, y):
        m = len(y)
        _, counts = np.unique(y, return_counts=True)
        return 1/m * counts
    
    def _means(self, X, y):
        m, n = X.shape
        classes = np.unique(y)
        return np.array([X[c == y.flatten()].sum(axis=0) / (c == y.flatten()).sum(axis=0) for c in classes])
    
    def _covariance_matrix(self, X, y):
        classes = np.unique(y)
        mu = self._means(X, y)
        return np.array([
            ((X[c == y.flatten()] - mu[i])**2).sum(axis=0) / (X[c == y.flatten()].shape[0]) for i, c in enumerate(classes)
        ])
    
    def _bayes_rule(self, X):
        return np.log(self.phi) - 1/2 * np.sum((X[:, np.newaxis, :] - self.mu)**2 / self.sigma**2, axis=2)
    
    def fit(self, X, y):
        self.phi = self._prior_probability(y)
        self.mu = self._means(X, y)
        self.sigma = self._covariance_matrix(X, y)

    def predict(self, X):
        return np.argmax(self._bayes_rule(np.array(X)), axis=1)
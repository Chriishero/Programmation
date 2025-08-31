import numpy as np

class GDA:
    def __init__(self):
        self.phi, self.mu, self.sigma = None, None, None

    def _prior_probability(self, y, classe):
        m = len(y)
        return 1/m * np.sum(y == classe)
    
    def _mean(self, X, y, classe):
        m_c = len(y[classe])
        return 1/m_c * np.sum(X[y == classe], axis=0)
    
    def _covariance_matrix(self, X, y, classe):
        m, n = X.shape
        return 1/m * np.sum(X - self._mean(X, y, classe)**2, axis=0)

    def fit(self, X, y):
        X, y = np.array(X), np.array(y)
        m, n, k = X.shape[0], X.shape[1], np.max(y) + 1
        self.phi = np.zeros(k)
        self.mu = np.zeros((k, n))
        self.sigma = np.zeros((k, n, n))

        for c in range(k):
            self.phi[c] = self._prior_probability(y, c)
            self.mu[c] = self._mean(X, y, c)
            self.sigma[c] = self._covariance_matrix(X, y, c)

    def _bayes_rules(self, X):
        pass
    
    def predict(self, X):
        return np.argmax(self._bayes_rules(np.array(X)), axis=1)

from sklearn.datasets import make_classification
X, y = make_classification(n_samples=500, n_features=10, n_informative=8, n_classes=2, random_state=0)

model = GDA()
model.fit(X, y)
print(model.phi)
print(model.mu)
print(model.sigma)
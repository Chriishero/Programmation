import numpy as np

class GDA:
    def __init__(self):
        self.phi, self.mu, self.sigma = None, None, None

    def _prior_probability(self, X_c, y):
        m = len(y)
        return 1/m * X_c.shape[0]
    
    def _mean(self, X_c):
        m_c = len(X_c)
        return 1/m_c * np.sum(X_c, axis=0)
    
    def _covariance_matrix(self, X_c):
        m, n = X_c.shape
        return 1/m * (X_c - self._mean(X_c)).T @ (X_c - self._mean(X_c))

    def fit(self, X, y):
        X, y = np.array(X), np.array(y)
        m, n, k = X.shape[0], X.shape[1], np.unique(y).shape[0]
        self.phi = np.zeros(k)
        self.mu = np.zeros((k, n))
        self.sigma = np.zeros((k, n, n))

        for c in range(k):
            X_c = X[y == c]
            self.phi[c] = self._prior_probability(X_c, y)
            self.mu[c] = self._mean(X_c)
            self.sigma[c] = self._covariance_matrix(X_c)

    def _bayes_rules(self, X):
        m, n, k = X.shape[0], X.shape[1], self.phi.shape[0]

        X = np.reshape(X, (1, m, n, 1))
        self.phi = np.reshape(self.phi, (k, 1, 1, 1))
        self.mu = np.reshape(self.mu, (k, 1, n, 1))
        self.sigma = np.reshape(self.sigma, (k, 1, n, n))

        p_y = self.phi
        p_x_y = (1 / (np.sqrt((2 * np.pi)**n * np.linalg.det(self.sigma))).reshape((k, 1, 1, 1))
                 * np.exp(-1/2 * (X - self.mu).transpose([0, 1, 3, 2]) @ np.linalg.inv(self.sigma) @ (X - self.mu)))
        p_y_x = p_x_y * p_y
        return p_y_x

    def predict(self, X):
        return np.argmax(self._bayes_rules(np.array(X)), axis=0).flatten()

from sklearn.datasets import make_classification
X, y = make_classification(n_samples=500, n_features=10, n_classes=2, random_state=0)

model = GDA()
model.fit(X, y)
y_pred = model.predict(X)

import matplotlib.pyplot as plt
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred,color="red")
from sklearn.metrics import accuracy_score
plt.title(f"{accuracy_score(y, y_pred)}")
plt.show()
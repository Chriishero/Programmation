import numpy as np

class GDA:
    def __init__(self):
        self.phi = None
        self.mu = None
        self.sigma = None

    def _prior_probability(self, X_c, y):
        m = len(y)
        return 1/m * X_c.shape[0]
    
    def _mean(self, X_c):
        m_c, n = X_c.shape
        return 1/m_c * np.sum(X_c, axis=0)
    
    def _covariance_matrix(self, X_c):
        m_c, n = X_c.shape
        return 1/m_c * (X_c - self._mean(X_c)).T @ (X_c - self._mean(X_c))
    
    def fit(self, X, y):
        X, y = np.array(X), np.array(y)
        m, n, k = X.shape[0], X.shape[1], np.unique(y).shape[0]

        self.phi = np.zeros((k))
        self.mu = np.zeros((k, n))
        self.sigma = np.zeros((k, n, n))

        for c in range(k):
            X_c = X[y == c]
            self.phi[c] = self._prior_probability(X_c, y)
            self.mu[c] = self._mean(X_c)
            self.sigma[c] = self._covariance_matrix(X_c) + np.eye(n)

    def _bayes_rules(self, X):
        m, n, k = X.shape[0], X.shape[1], self.phi.shape[0]

        p_y = self.phi
        p_y_x = np.zeros((m, k))
        for c in range(k):
            p_x_y = (1 / np.sqrt((2 * np.pi)**n * np.linalg.det(self.sigma[c])) * 
                     (-1/2 * np.sum((X - self.mu[c]) @ np.linalg.inv(self.sigma[c]) * (X - self.mu[c]), axis=1)))
            p_y_x[:, c] = p_x_y * p_y[c]
        return p_y_x
    
    def predict(self, X):
        return np.argmax(self._bayes_rules(np.array(X)), axis=1)

    
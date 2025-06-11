import numpy as np
from sklearn.metrics import r2_score, accuracy_score
from sklearn.model_selection import train_test_split

class LogisticRegression:
    def __init__(self, n_iteration=100, learning_rate=0.1, method='gradient_descent'):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate 
        self.method = method

        self.theta = None
    
    def _sigmoid(self, X):
        return 1 / (1 + np.exp(-X @ self.theta))
    
    def _likelihood_function(self, y_pred, y):
        m = len(y)
        return 1/m * np.sum(y * np.log(y_pred + 1e-15) + (1 - y) * np.log(1 - y_pred))
    
    def _gradient_function(self, X, y):
        m, n = X.shape
        h = self._sigmoid(X)
        return 1/m * X.T @ (h - y)
    
    def _newton_raphson_step(self, X, y):
        m, n = X.shape
        h = self._sigmoid(X)
        D = np.diagflat(h * (1 - h))
        H = -1/m * (X.T @ D @ X)
        H_reg = H - 1e-15 * np.eye(H.shape[0])
        return np.linalg.inv(H_reg) @ self._gradient_function(X, y)
    
    def _optimisation(self, X, y):
        m, n = X.shape
        self.theta = np.zeros(n)
        for i in range(self.n_iteration):
            if self.method == "newton":
                self.theta -= self.learning_rate * self._newton_raphson_step(X, y)
            elif self.method == "gradient_descent":
                self.theta += self.learning_rate * self._gradient_function(X, y)

    def fit(self, X, y):
        X = np.hstack((X, np.ones((X.shape[0], 1))))
        self._optimisation(np.array(X), np.array(y))

    def predict(self, X):
        X = np.hstack((X, np.ones((X.shape[0], 1))))
        return (self._sigmoid(np.array(X)) >= 0.5).astype(int)
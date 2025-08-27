import numpy as np

class LogisticRegression:
    def __init__(self, n_iteration=100, learning_rate=0.2, method="newton_raphson"):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.method = method

        self.theta = None

    def _logits_function(self, X):
        return X @ self.theta
    
    def _sigmoid_function(self, X):
        return 1 / (1 + np.exp(-self._logits_function(X)))
    
    def _likelihood(self, X, y):
        m, n = X.shape
        h = self._sigmoid_function(X)
        return 1/m * np.sum(y * np.log(h + 1e-15) + (1 - y) * np.log(1 - h))
    
    def _gradient_function(self, X, y):
        m, n = X.shape
        h = self._sigmoid_function(X)
        return 1/m * X.T @ (y - h)
    
    def _newton_raphson_step(self, X, y):
        m, n = X.shape
        h = self._sigmoid_function(X)
        H = -1/m * X.T @ np.diagflat(h * (1 - h)) @ X
        H -= 1e-15 * np.eye(H.shape[1])
        return np.linalg.inv(H) @ self._gradient_function(X, y)
    
    def _optimisation_function(self, X, y):
        m, n = X.shape
        self.theta = np.zeros(n)
        for i in range(self.n_iteration):
            if self.method == "gradient_descent":
                self.theta += self.learning_rate * self._gradient_function(X, y)
            elif self.method == "newton_raphson":
                self.theta -= self._newton_raphson_step(X, y)

    def fit(self, X, y):
        self._optimisation_function(np.array(X), np.array(y))

    def predict(self, X):
        return self._sigmoid_function(X) >= 0.5
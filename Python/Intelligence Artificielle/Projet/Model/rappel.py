import numpy as np

class LinearRegression:
    def __init__(self, n_iteration=100, learning_rate=0.2, method="gradient descent"):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.method = method

        self.theta = None

    def _hypothesis(self, X):
        return X @ self.theta
    
    def _cost_function(self, X, y):
        m, n = X.shape
        h = self._hypothesis(X)
        return 1/m * np.sum((y - h)**2)
    
    def _gradient_function(self, X, y):
        m, n = X.shape
        h = self._hypothesis(X)
        return 1/m * X.T @ (y - h)
    
    def _gradient_descent(self, X, y):
        m, n = X.shape
        self.theta = np.zeros((n, np.unique(y).shape[0]))
        for i in range(self.n_iteration):
            self.theta += self.learning_rate * self._gradient_function(X, y)

    def _normal_equation(self, X, y):
        return np.linalg.inv(X.T @ X) @ X.T @ y
    
    def fit(self, X, y):
        X, y = np.array(X), np.array(y)
        y = y.reshape(-1, 1)
        if self.method == "normal equation":
            self.theta = self._normal_equation(X, y)
        if self.method == "gradient descent":
            self._gradient_descent(X, y)

    def predict(self, X):
        return self._hypothesis(np.array(X))
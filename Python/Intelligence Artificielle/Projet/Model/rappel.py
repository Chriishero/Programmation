import numpy as np

class LocallyWeightedRegression:
    def __init__(self, n_iteration=100, learning_rate=0.2, tau=0.5, method="gradient_descent"):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.tau = tau
        self.method = method

        self.W = self.theta = None

    def _hypothesis(self, X):
        return X @ self.theta
    
    def _weight_function(self, X, x):
        return np.diag(np.exp(-np.sum((X - x)**2, axis=1) / (2 * self.tau**2)))

    def _cost_function(self, X, y):
        m, n = X.shape
        h = self._hypothesis(X)
        return 1/m * np.sum(self.W @ (h - y)**2)
    
    def _gradient_function(self, X, y):
        m, n = X.shape
        h = self._hypothesis(X)
        return 1/m * X.T @ self.W @ (h - y)
    
    def _gradient_descent(self, X, y):
        m, n = X.shape
        self.theta = np.zeros((n, 1))
        for i in range(self.n_iteration):
            self.theta -= self.learning_rate * self._gradient_function(X, y)

    def _normal_equation(self, X, y):
        self.theta = np.linalg.inv(X.T @ self.W @ X) @ X.T @ self.W @ y

    def predict(self, X, y, x):
        X, y = np.array(X), np.array(y)
        x = x.reshape(1, -1)
        self.W = self._weight_function(X, x)
        
        if self.method == "gradient_descent":
            self._gradient_descent(X, y)
        elif self.method == "normal_equation":
            self._normal_equation(X, y)

        return self._hypothesis(x)
    
X = np.linspace(-3, 3, 500).reshape(-1, 1)
y = X**3 - 3 * X + np.random.randn(*X.shape) * 0.5
X = np.hstack((X, np.ones_like(X)))

model = LocallyWeightedRegression()
y_pred = [model.predict(X, y, x).item() for x in X]

import matplotlib.pyplot as plt
from sklearn.metrics import r2_score
plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c="red")
plt.title(f"{r2_score(y, y_pred)}")
plt.legend()
plt.show()
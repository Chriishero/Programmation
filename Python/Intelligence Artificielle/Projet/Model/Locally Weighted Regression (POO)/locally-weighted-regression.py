import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import r2_score

class LocallyWeightedRegression:
    def __init__(self, n_iteration=100, learning_rate=0.2, tau=0.9, method="gradient descent"):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.tau = tau
        self.method = method
        
        self.W = None
        self.theta = None

    def _hypothesis(self, X):
        return X @ self.theta
    
    def _weight_function(self, X, x):
        return np.diag(np.exp(-np.sum((X - x)**2, axis=1) / (2 * self.tau**2)))
    
    def _gradient(self, X, y):
        m = X.shape[0]
        h = self._hypothesis(X)
        return 1/m * X.T @ self.W @ (h - y)
    
    def _gradient_descent(self, X, y):
        m, n = X.shape
        self.theta = np.zeros((n, 1))
        for _ in range(self.n_iteration):
            self.theta -= self.learning_rate * self._gradient(X, y)

    def _normal_equation(self, X, y):
        return np.linalg.pinv(X.T @ self.W @ X) @ X.T @ self.W @ y
    
    def predict(self, X, y, x):
        X = np.array(X)
        y = np.array(y).reshape(-1, 1)
        x = x.reshape(1, -1)

        self.W = self._weight_function(X, x)

        if self.method == "gradient descent":
            self._gradient_descent(X, y)
        elif self.method == "normal equation":
            self.theta = self._normal_equation(X, y)

        return self._hypothesis(x)

X = np.linspace(-3, 3, 500).reshape(-1, 1)
y = X**3 - 3 * X + np.random.randn(*X.shape) * 0.5
X = np.hstack((X, np.ones_like(X)))

model = LocallyWeightedRegression(tau=0.5, method="normal equation")
y_pred = [model.predict(X, y, x).item() for x in X]

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, color='red')
plt.title(f"{r2_score(y, y_pred)}")
plt.legend()
plt.show()

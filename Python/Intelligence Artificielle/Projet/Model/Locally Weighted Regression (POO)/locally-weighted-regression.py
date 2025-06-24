import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression
from sklearn.metrics import r2_score

x, y = make_regression(n_samples=500, n_features=10, noise=10, random_state=0)
X = np.hstack((x, np.ones((x.shape[0], 1))))
y = y.reshape((y.shape[0], 1))

class LocallyWeightedRegression:
    def __init__(self, n_iteration=100, learning_rate=0.1, tau=1, method="gradient descent"):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.tau = tau
        self.method = method
        self.theta = None
        self.cost_history = None

    def hypothesis(self, X):
        return X @ self.theta
    
    def weight_function(self, X, x):
        x = x.reshape(1, -1)
        return np.exp(-np.sum((X - x)**2, axis=1) / 2 * self.tau**2)
    
    def cost_function(self, W, X, y):
        m = len(y)
        h = self.hypothesis(X)
        return 1/m * np.sum(W @ (y - h)**2)
    
    def gradient(self, W, X, y):
        m = len(y)
        h = self.hypothesis(X)
        return 1/m * X.T @ W @ (y - h)
    
    def gradient_descent(self, X, y, x):
        m = len(y)
        self.cost_history = np.zeros((self.n_iteration, 1))
        W = np.diag(self.weight_function(X, x))
        for i in range(self.n_iteration):
            self.theta = self.theta + self.learning_rate * self.gradient(W, X, y)
            self.cost_history[i] = self.cost_function(W, X, y)

    def normal_equation(self, X, y, x):
        W = np.diag(self.weight_function(X, x))
        self.theta = np.linalg.inv(X.T @ W @ X) @ X.T @ W @ y

    def predict(self, X, y, x):
        m, n = X.shape
        self.theta = np.zeros((n, 1))
        if self.method == "gradient descent":
            self.gradient_descent(X, y, x)
        elif self.method == "normal equation":
            self.normal_equation(X, y, x)

        return self.hypothesis(x)


model = LocallyWeightedRegression(n_iteration=1000, learning_rate=0.2, tau=0.9, method="gradient descent")
model = LocallyWeightedRegression()
y_preds = [model.predict(X, y, x) for x in X]
print(f'{r2_score(y, y_preds)}')

plt.figure()
plt.plot(range(model.n_iteration), model.cost_history, label="Évolution de la fonction coût")
plt.show()

import numpy as np
from sklearn.datasets import make_regression
import matplotlib.pyplot as plt

n_samples = 500
n_features = 10

x, y = make_regression(n_features=n_features, n_samples=n_samples, noise=10, random_state=0)
X = np.hstack((x, np.ones((x.shape[0], 1))))
y = y.reshape(y.shape[0], 1)

class LinearRegression:
    def __init__(self, n_iteration, learning_rate, method):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.method = method
        self.theta = None
        self.cost_history = None

    def hypothesis(self, X):
        return X @ self.theta
    
    def cost_function(self, X, y):
        m = len(y)
        h = self.hypothesis(X)
        return 1/m * np.sum((h - y)**2)
    
    def gradient(self, X, y):
        m = len(y)
        h = self.hypothesis(X)
        return 1/m * X.T @ (h - y)
    
    def gradient_descent(self, X, y):
        m, n = X.shape
        k = np.unique(y).shape[0]
        self.theta = np.ones((n, k))
        self.cost_history = np.zeros(self.n_iteration)
        for i in range(self.n_iteration):
            self.theta = self.theta - self.learning_rate * self.gradient(X, y)
            self.cost_history[i] = self.cost_function(X, y)
        return self.cost_history, self.theta
    
    def normal_equation(self, X, y):
        self.theta = np.linalg.inv(X.T @ X) @ X.T @ y

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)
        if self.method == "gradient descent":
            self.gradient_descent(X, y)
        elif self.method == "normal equation":
            self.normal_equation(X, y)

    def predict(self, X):
        X = np.array(X)
        return self.hypothesis(X)
    
model = LinearRegression(n_iteration=100, learning_rate=0.1, method="normal equation")
model.fit(X, y)
y_pred = model.predict(X)
print(model.cost_function(X, y))

# Uniquement avec la descente de gradient
# plt.figure()
# plt.plot(range(model.n_iteration), model.cost_history, label="Évolution de la fonction coût")

plt.figure()
plt.scatter(x[:, 0], y)
plt.plot(x[:, 0], y_pred, c="r")
plt.show()

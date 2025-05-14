import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.metrics import accuracy_score

X, y = make_classification(n_samples=500, n_features=10, n_informative=2, n_classes=2, random_state=0)
y = y * 2 - 1

class SVM:
    def __init__(self, n_iteration=25, kernel='RBF', regularization=1, gamma=0.5, polynomial_constant=1, polynom_degree=2):
        self.n_iteration = n_iteration
        self.kernel = kernel
        self.C = regularization
        self.gamma = gamma
        self.polynomial_constant = polynomial_constant
        self.polynom_degree = polynom_degree
        self.X_train = None
        self.y_train = None
        self.K, self.alpha = None, None
        self.b = 0
        self.cost_history = np.zeros(n_iteration)

    def kernel_function(self, X, Z):
        if self.kernel == "linear":
            return X.T @ Z
        if self.kernel == "polynomial":
            return (X.T @ Z + self.polynomial_constant)**self.polynom_degree
        if self.kernel == "RBF":
            return np.exp(-self.gamma * np.linalg.norm(X[:, np.newaxis, :] - Z, axis=2)**2)
        
    def dual_objective_function(self, y):
        return np.sum(self.alpha) - 1/2 * self.alpha @ ((np.outer(y, y) * self.K) @ self.alpha)
    
    def sequential_minimal_optimization(self, X, y):
        m, n = X.shape
        self.alpha = np.zeros(m)
        for iteration in range(self.n_iteration):
            for i in range(m):
                j = np.random.choice([k for k in range(m) if k != i])

                old_alpha_i = self.alpha[i]
                old_alpha_j = self.alpha[j]

                zeta = old_alpha_i * y[i] + old_alpha_j * y[j]
                self.alpha[j] = (1 - y[i] * self.K[i, j] * zeta) / (self.K[j, j] - self.K[i, j])
                self.alpha[j] = np.clip(self.alpha[j], 0, self.C)

                self.alpha[i] = old_alpha_i + y[i] * y[j] * (old_alpha_j - self.alpha[j])
                self.alpha[i] = np.clip(self.alpha[i], 0, self.C)

                E_i = np.sum(self.alpha[i] * y.ravel() * self.K[i, :]) + self.b - y[i]
                E_j = np.sum(self.alpha[j] * y.ravel() * self.K[j, :]) + self.b - y[j]
                b1 = self.b - E_i - y[i] * (self.alpha[i] - old_alpha_i) * self.K[i, j] - y[j] * (self.alpha[j] - old_alpha_j) * self.K[i, j]
                b2 = self.b - E_j - y[j] * (self.alpha[i] - old_alpha_i) * self.K[i, j] - y[j] * (self.alpha[j] - old_alpha_j) * self.K[j, j]
                self.b = (b1 + b2) / 2

            self.cost_history[iteration] = self.dual_objective_function(y)

    def fit(self, X, y):
        self.X_train = X = np.array(X)
        self.y_train = y =  np.array(y)
        self.K = self.kernel_function(X, X)
        self.sequential_minimal_optimization(X, y)

    def predict(self, X):
        X = np.array(X)
        K = self.kernel_function(X, self.X_train)
        return np.sign(np.sum(self.alpha * self.y_train * K, axis=1) + self.b)
    
model = SVM()
model.fit(X, y)
y_pred = model.predict(X)

from sklearn.metrics import accuracy_score

plt.figure()
plt.plot(range(model.n_iteration), model.cost_history)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c='r')
plt.title(f"{accuracy_score(y, y_pred)}")
plt.show()
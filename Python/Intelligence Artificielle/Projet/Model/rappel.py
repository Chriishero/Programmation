import numpy as np

class SVM:
    def __init__(self, n_iteration=100, kernel="RBF", regularization=1, polynom_degree=4, polynomial_constant=1.0, gamma=1.0):
        self.n_iteration = n_iteration
        self.kernel = kernel
        self.C = regularization
        self.polynomial_constant = polynomial_constant
        self.polynom_degree = polynom_degree
        self.polynomial_constant = polynomial_constant
        self.gamma = gamma

        self.X_train, self.y_train = None, None
        self.K = None
        self.alpha = None
        self.b = 0

    def _kernel_function(self, X, Z):
        if self.kernel == "linear":
            return X @ Z.T
        elif self.kernel == "polynomial":
            return (X @ Z.T + self.polynomial_constant)**self.polynom_degree
        elif self.kernel == "RBF":
            return np.exp(-self.gamma * np.linalg.norm((X[:, np.newaxis, :] - Z), axis=2)**2)
        
    def _dual_objective_function(self, y):
        return 1/2 * np.sum(self.alpha) * (self.alpha @ (self.K * np.outer(y, y)) @ self.alpha)
    
    def _sequential_minimal_optimisation(self, X, y):
        m, n = X.shape
        self.alpha = np.zeros(m)
        self.b = 0
        for iter in range(self.n_iteration):
            for i in range(m):
                j = np.random.choice([k for k in range(m) if k != i])

                old_alpha_i = self.alpha[i]
                old_alpha_j = self.alpha[j]

                zeta = old_alpha_i * y[i] + old_alpha_j * y[j]
                self.alpha[j] = (1 - y[i] * self.K[i, j] * zeta) / (self.K[j, j] - self.K[i, j])
                self.alpha[j] = np.clip(self.alpha[j], 0, self.C)

                self.alpha[i] += y[i] * y[j] * (old_alpha_j - self.alpha[j])
                self.alpha[i] = np.clip(self.alpha[i], 0, self.C)

                E_i = np.sum(self.alpha * y.ravel() * self.K[i, :]) + self.b - y[i]
                E_j = np.sum(self.alpha * y.ravel() * self.K[j, :]) + self.b - y[j]

                b1 = self.b - E_i - y[i] * (self.alpha[i] - old_alpha_i) * self.K[i, j] - y[j] * (self.alpha[j] - old_alpha_j) * self.K[i, j]
                b2 = self.b - E_j - y[i] * (self.alpha[i] - old_alpha_i) * self.K[i, j] - y[j] * (self.alpha[j] - old_alpha_j) * self.K[j, j]
                self.b = (b1 + b2) / 2

    def fit(self, X, y):
        X, y = self.X_train, self.y_train = np.array(X), np.array(y)
        self.K = self._kernel_function(X, X)
        self._sequential_minimal_optimisation(X, y)

    def predict(self, X):
        X = np.array(X)
        K = self._kernel_function(X, self.X_train)
        return np.sign(np.sum(self.alpha * self.y_train * K, axis=1) + self.b)
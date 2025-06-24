import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification

x, y = make_classification(n_samples=500, n_features=10, n_classes=2, random_state=0)
X = np.hstack((x, np.ones((x.shape[0], 1))))
y = y.reshape((y.shape[0], 1))

class LogisticRegression:
    def __init__(self, n_iteration=100, learning_rate=0.1, method="gradient descent"):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.method = method
        self.theta = None
        self.cost_history = None

    def sigmoid(self, X):
        return 1 / (1 + np.exp(-X @ self.theta))
    
    def likelihood(self, y_pred, y):
        m = len(y)
        epsilon = 1e-15
        y_pred = np.clip(y_pred, epsilon, 1 - epsilon) # évite que y_pred = 0, donc un log(0)
        return 1/m * np.sum(y * np.log(y_pred) + (1 - y) * np.log(1 - y_pred))
    
    def gradient(self, X, y):
        m = len(y)
        h = self.sigmoid(X) 
        return 1/m * X.T @ (y - h)
    
    def newton_raphson_step(self, X, y):
        m = len(y)
        h = self.sigmoid(X)
        D = np.diagflat(h * (1 - h)) # variance de la distribution de Bernouilli
        # diagflat() : transforme ce vecteur en une matrice diagonal de dimension (m, m), qui est la matrice des variances
        
        H = -1/m * (X.T @ D @ X) 
        H_reg = H - 1e-15 * np.eye(H.shape[0]) # H peut être singulière (non-réversible) si les colonnes de X sont colinéaires
        # np.eye() : crée une matrice identité de taille (n, n)
        # 1e-15 : petite valeur ajouté aux diagonales, ce qui empêche H d'être singulière

        return np.linalg.inv(H_reg) @ self.gradient(X, y) # l'(theta)/l''(theta)
    
    def optimisation(self, X, y):
        m, n = X.shape
        self.theta = np.zeros((n, 1))
        self.cost_history = np.zeros(self.n_iteration)
        for i in range(self.n_iteration):
            if self.method == "gradient descent":
                self.theta = self.theta + self.learning_rate * self.gradient(X, y)
            elif self.method == "newton method":
                self.theta = self.theta - self.newton_raphson_step(X, y)
            self.cost_history[i] = self.likelihood(self.sigmoid(X), y)
        return self.cost_history, self.theta
    
    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)
        self.optimisation(X, y)

    def predict(self, X):
        X = np.array(X)
        return (self.sigmoid(X) >= 0.5).astype(int)
    
model = LogisticRegression(n_iteration=3, learning_rate=0.1, method="newton method")
model.fit(X, y)
y_pred = model.predict(X)

print(model.likelihood(y_pred, y))

plt.figure()
plt.plot(range(model.n_iteration), model.cost_history, label="Évolution de la fonction coût")

plt.figure()
plt.scatter(x[:, 0], y)
plt.plot(x[:, 0], y_pred, c="r")
plt.show()
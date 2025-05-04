import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression, make_classification

x, y = make_classification(n_samples=500, n_features=10, n_classes=4, n_informative=2, n_clusters_per_class=1, random_state=0)
X = np.hstack((x, np.ones((x.shape[0], 1))))

class Softmax:
    def __init__(self, n_iteration=1000, learning_rate=0.01):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.theta = None

    def softmax(self, X):
        Z = X @ self.theta
        Z -= np.max(Z, axis=1, keepdims=True)  # Évite les problèmes numériques
        return np.exp(Z) / np.sum(np.exp(Z), axis=1, keepdims=True)

    def cross_entropy(self, X, y):
        m = len(y)
        predicted_probability = self.softmax(X)
        true_probability = predicted_probability[range(m), y]

        epsilon = 1e-15
        return -np.sum(np.log(true_probability + epsilon)) / m  # Moyenne de l'entropie croisée

    def gradient(self, X, y):
        m = len(y)
        predicted_probability = self.softmax(X)
        true_probability_onehot = np.zeros_like(predicted_probability)
        true_probability_onehot[np.arange(m), y] = 1
        return (1 / m) * X.T @ (predicted_probability - true_probability_onehot)

    def gradient_descent(self, X, y):
        m, n = X.shape
        k = np.unique(y).shape[0]  # Nombre de classes
        self.theta = np.zeros((n, k))  # Initialisation des poids
        cost_history = np.zeros(self.n_iteration)

        for i in range(self.n_iteration):
            gradient = self.gradient(X, y)
            self.theta  = self.theta - self.learning_rate * gradient
            cost_history[i] = self.cross_entropy(X, y)

        return cost_history

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)
        self.gradient_descent(X, y)

    def predict(self, X):
        X = np.array(X)
        y_pred_prob = self.softmax(X, self.theta)
        return np.argmax(y_pred_prob, axis=1)  # Prendre la classe avec la proba max


model = Softmax(400, 0.1)
model.fit(X, y)
y_pred = model.predict(X)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c='r')
plt.show()
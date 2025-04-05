import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
import seaborn as sns

class Softmax:
    def __init__(self, n_iteration=1000, learning_rate=0.01):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.theta = None

    def softmax(self, X, theta):
        Z = X @ theta
        Z -= np.max(Z, axis=1, keepdims=True)  # Évite les problèmes numériques
        return np.exp(Z) / np.sum(np.exp(Z), axis=1, keepdims=True)

    def cross_entropy(self, X, y, theta):
        m = len(y)
        predicted_probability = self.softmax(X, theta)
        true_probability = predicted_probability[range(m), y]

        epsilon = 1e-15
        return -np.sum(np.log(true_probability + epsilon)) / m  # Moyenne de l'entropie croisée

    def gradient(self, X, y, theta):
        m = len(y)
        predicted_probability = self.softmax(X, theta)
        true_probability_onehot = np.zeros_like(predicted_probability)
        true_probability_onehot[np.arange(m), y] = 1
        return (1 / m) * X.T @ (predicted_probability - true_probability_onehot)

    def gradient_descent(self, X, y):
        m, n = X.shape
        k = np.unique(y).shape[0]  # Nombre de classes
        self.theta = np.zeros((n, k))  # Initialisation des poids
        cost_history = np.zeros(self.n_iteration)

        for i in range(self.n_iteration):
            gradient = self.gradient(X, y, self.theta)
            self.theta  = self.theta - self.learning_rate * gradient
            cost_history[i] = self.cross_entropy(X, y, self.theta)

        return cost_history

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)
        self.gradient_descent(X, y)

    def predict(self, X):
        X = np.array(X)
        y_pred_prob = self.softmax(X, self.theta)
        return np.argmax(y_pred_prob, axis=1)  # Prendre la classe avec la proba max
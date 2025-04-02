import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification

n_samples = 500
n_features = 10

x, y = make_classification(n_samples=n_samples, n_features=n_features, n_classes=2, random_state=0)
y = y.reshape(y.shape[0], 1)
X = np.hstack((x, np.ones((x.shape[0], 1))))

theta = np.random.randn(n_features+1, 1)

def model(X, theta):
    return X.dot(theta)

def sigmoid(X, theta):
    return 1/(1 + np.exp(-model(X, theta)))

def likelihood(h, y):
    m = len(y)
    epsilon = 1e-15  # Petite constante pour éviter log(0)
    h = np.clip(h, epsilon, 1 - epsilon)  # Limiter h entre epsilon et 1-epsilon
    return - (1/m * np.sum(y * np.log(h) + (1 - y) * np.log(1 - h))) # somme, car on veut récupérer qu'une seule valeur

def gradient(X, y, theta):
    m = len(y)
    h = sigmoid(X, theta)
    return 1/m * -X.T.dot(y - h)

def gradient_ascent(X, y, theta, n_iteration, learning_rate):
    cost_history = np.zeros(n_iteration)
    for i in range(n_iteration):
        theta = theta + learning_rate * gradient(X, y, theta)
        cost_history[i] = likelihood(sigmoid(X, theta), y)
    return cost_history, theta

n_iteration = 300
learning_rate = 0.1
cost_history, theta = gradient_ascent(X, y, theta, n_iteration, learning_rate)
prediction = (sigmoid(X, theta) >= 0.5).astype(int)
print(likelihood(prediction, y))

plt.figure()
plt.plot(range(n_iteration), cost_history)

plt.figure()
plt.scatter(x[:, 0], y)
plt.plot(x[:, 0], prediction, c='r')
plt.show()

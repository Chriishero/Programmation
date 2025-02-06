import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression

n_samples = 500
n_features = 10

x, y = make_regression(n_samples=n_samples, n_features=n_features, noise=10, random_state=0)
y = y.reshape(y.shape[0], 1)
X = np.hstack((x, np.ones((x.shape[0], 1))))

theta = np.random.randn(n_features+1, 1)

def model(X, theta):
    return X.dot(theta)

def cost_function(h, y):
    m = len(y)
    return 1/m * np.sum(np.square(h - y))

def gradient(X, y, theta):
    h = model(X, theta)
    residuals = h - y
    m = len(y)
    return 1/m * X.T.dot(residuals)

def gradient_descent(X, y, theta, n_iteration, learning_rate):
    cost_history = np.zeros(n_iteration)
    for i in range(n_iteration):
        theta = theta - learning_rate * gradient(X, y, theta)
        cost_history[i] = cost_function(model(X, theta), y)
    return cost_history, theta

n_iteration = 100
learning_rate = 0.1
cost_history, theta = gradient_descent(X, y, theta, n_iteration, learning_rate)
prediction = model(X, theta)
print(cost_function(prediction, y))

plt.figure()
plt.plot(range(n_iteration), cost_history, label="Évolution de la fontion coût")

plt.figure()
plt.scatter(x[:, 0], y)
plt.plot(x[:, 0], prediction, c="r")
plt.show()
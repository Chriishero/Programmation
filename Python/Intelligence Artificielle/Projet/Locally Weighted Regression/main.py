import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression, make

n_features = 5
n_samples = 500

x, y = make_regression(n_samples=n_samples, n_features=n_features, noise=10, random_state=0)

y = y.reshape((y.shape[0], 1))
X = np.hstack((x, np.ones(x.shape[0], 1)))

theta = np.zeros(n_features+1, 1)

def model(X, theta):
    return X.dot(theta)

def cost_function(h, y, tau):
    m = len(y)
    w = np.exp(-(X[:, :] - X[0, :])**2 / 2*np.square(tau))
    return 1/m * np.sum(w.dot(np.square(y - h)))

def gradient(X, ytheta):
    h = model(X, y)
    residuals = h - y
    m = len(y)
    return 1/m * X.T.dot(w * residuals)

def gradient_descent(X, y, theta, n_iterations, learning_rate, tau):
    cost_history = np.zeros(n_iterations)
    for i in range(n_iterations):
        theta = theta - learning_rate

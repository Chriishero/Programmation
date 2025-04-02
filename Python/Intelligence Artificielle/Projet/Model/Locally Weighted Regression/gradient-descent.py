import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression

n_features = 5
n_samples = 500

x, y = make_regression(n_features=n_features, n_samples=n_samples, noise=10, random_state=0)
X = np.hstack((x, np.ones((x.shape[0], 1))))
y = y.reshape([y.shape[0], 1])

def model(X, theta):
    return X @ theta

def weight(X, x, tau):
    x = x.reshape(1, -1)
    return np.exp(-np.sum((X - x)**2 / 2, axis=1) * tau**2)

def cost_function(W, h, y):
    return np.sum(W @ (h - y)**2)

def gradient(W, X, theta, y):
    m = len(y)
    h = model(X, theta)
    return 1/m * 2 * X.T @ W @ (h - y)

def gradient_descent(X, x, y, learning_rate, n_iterations, tau):
    cost_history = np.zeros((n_iterations, 1))
    theta = np.zeros((n_features+1, 1))
    W = np.diag(weight(X, x, tau))
    for i in range(n_iterations):
        theta = theta - learning_rate * gradient(W, X, theta, y)
        cost_history[i] = cost_function(W, model(x, theta), y)

    return theta, cost_history

x = np.hstack((np.random.randn(1, n_features), np.ones((1, 1)))) 

learning_rate = 0.01
n_iterations = 1000
tau = 1.3
theta, cost_history = gradient_descent(X=X, x=x, y=y, learning_rate=learning_rate, n_iterations=n_iterations, tau=tau)
prediction = model(x, theta)
print(prediction)

plt.figure()
plt.plot(range(n_iterations), cost_history)
plt.show()
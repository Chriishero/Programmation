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

def cost_function(h, theta):
    m = len(y)
    return 1/m * np.sum(np.square(h - y))

def normal_equation(X, y):
    theta = np.linalg.inv(X.T.dot(X)).dot(X.T).dot(y)
    return theta

theta = normal_equation(X, y)
prediction = model(X, theta)
print(cost_function(prediction, y))

plt.figure()
plt.plot(x[:, 0], prediction, c="r")
plt.scatter(x[:, 0], y)
plt.show()
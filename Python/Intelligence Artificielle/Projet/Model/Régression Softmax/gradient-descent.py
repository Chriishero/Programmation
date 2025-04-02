import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification

n_samples = 500
n_features = 10
n_classes = 4

x, y = make_classification(n_samples=n_samples, n_features=n_features, n_classes=4, n_informative=2, n_clusters_per_class=1, random_state=0)
X = np.hstack((x, np.ones((x.shape[0], 1))))
#y = y.reshape((y.shape[0], 1))

theta = np.zeros((n_features+1, n_classes))

print(X.shape)
print(theta.shape)
print(y.shape)

def model(X, theta):
    return X.dot(theta)

def cross_entropy(h, y):
    global predicted_probability, true_probatility
    predicted_probability = np.exp(h) / np.sum(np.exp(h), axis=1, keepdims=True) 
    # keepdims préserve les dimensions de la matrice après une opération comme sum, mean, etc
    # (n_samples, 1) au lieu de (n_samples,)

    # Probabilité prédite pour la classe correspondante à chaque échantillons x
    true_probatility = predicted_probability[range(len(y)), y]
    
    return np.sum(-np.log(true_probatility))

def gradient(X, theta):
    m = len(y)
    true_probatility_onehot = np.zeros((predicted_probability.shape))
    true_probatility_onehot[range(len(y)), y] = 1 # remplir la classe correcte avec 1
    return 1/m * X.T.dot(predicted_probability - true_probatility_onehot) # dérivé partielle de la cross_entropy en fonction de theta

def gradient_descent(X, y, theta, n_iterations, learning_rate):
    cost_history = np.zeros(n_iterations)
    h = model(X, theta)
    cross_entropy(h, y)
    
    for i in range(n_iterations):
        theta = theta - learning_rate * gradient(X, theta)
        h = model(X, theta)
        cost_history[i] = cross_entropy(h, y)
        
    return theta, cost_history

n_iterations = 400
learning_rate = 0.1

theta, cost_history = gradient_descent(X, y, theta, n_iterations, learning_rate)
y_pred_probability = model(X, theta) > 0
y_pred = np.argmax(y_pred_probability, axis=1)

plt.figure()
plt.plot(range(n_iterations), cost_history)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c='r')
plt.show()
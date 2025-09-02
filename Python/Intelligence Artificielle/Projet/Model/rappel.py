import numpy as np

class SoftmaxRegressor:
    def __init__(self, n_iteration=100, learning_rate=0.3):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate

        self.method = None

    def _softmax(self, X):
        logits = X @ self.theta
        exp_logits = np.exp(logits - np.max(logits, axis=1, keepdims=True))
        return exp_logits / np.sum(exp_logits, axis=1, keepdims=True)
    
    def _loss_function(self, X, y):
        m, n = X.shape
        proba = self._softmax(X)
        y_true = proba[np.arange(m), y]
        return 1/m * np.sum(-np.log(y_true + 1e-15))
    
    def _gradient_function(self, X, y):
        m, n = X.shape
        proba = self._softmax(X)
        y_onehot = np.zeros_like(proba)
        y_onehot[np.arange(m), y] = 1
        return 1/m * X.T @ (proba - y_onehot)
    
    def _gradient_descent(self, X, y):
        m, n = X.shape
        k = np.unique(y).shape[0]
        self.theta = np.zeros((n, k))
        for i in range(self.n_iteration):
            self.theta -= self.learning_rate * self._gradient_function(X, y)

    def fit(self, X, y):
        self._gradient_descent(np.array(X), np.array(y))

    def predict(self, X):
        return np.argmax(self._softmax(X), axis=1)

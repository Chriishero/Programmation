import numpy as np

class SoftmaxRegression:
    def __init__(self, n_iteration=100, learning_rate=0.2):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate

        self.theta = None

    def _logits_function(self, X):
        return X @ self.theta
    
    def _softmax_function(self, logits):
        exp_logits = np.exp(logits - np.max(logits, axis=1, keepdims=True))
        return exp_logits / np.sum(exp_logits, axis=1, keepdims=True)
    
    def _loss_function(self, X, y):
        m, n = X.shape
        proba = self._softmax_function(self._logits_function(X))
        y_true = proba[np.arange(m), y]
        return 1/m * np.sum(-np.log(y_true + 1e-15))
    
    def _gradient_function(self, X, y):
        m, n = X.shape
        proba = self._softmax_function(self._logits_function(X))
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
        logits = self._logits_function(X)
        return np.argmax(self._softmax_function(logits), axis=1)
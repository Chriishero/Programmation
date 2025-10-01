import numpy as np
from sklearn.tree import DecisionTreeClassifier

class AdaBoostClassifier:
    def __init__(self, n_estimators=200):
        self.n_estimators = n_estimators

        self.k = None
        self.w_ = None
        self.estimators_ = []
        self.alphas_ = []

    def _train_estimators(self, X, y):
        m, n, self.k = X.shape[0], X.shape[1], np.unique(y).shape[0]
        self.w_ = np.ones(m) / m

        for _ in range(self.n_estimators):
            model = DecisionTreeClassifier(max_depth=2)
            model.fit(X, y, sample_weight=self.w_)
            y_pred = model.predict(X)

            err = np.sum(self.w_ * (y_pred != y)) / np.sum(self.w_)
            if err > 1 - 1 / self.k or err <= 1e-15:
                break
            alpha = np.log((1 - err) / err) + np.log(self.k - 1)

            self.estimators_.append(model)
            self.alphas_.append(alpha)

            self.w_ = self.w_ * np.exp(alpha * (y_pred != y))
            self.w_ /= np.sum(self.w_)

    def fit(self, X, y):
        X, y = np.array(X), np.array(y)
        self._train_estimators(X, y)

    def predict(self, X):
        X = np.array(X)
        m, n = X.shape
        prediction_weights = np.zeros((m, self.k))
    
        for i in range(self.n_estimators):
            y_pred = self.estimators_[i].predict(X)
            prediction_weights[np.arange(m), y_pred] += self.alphas_[i]

        return np.argmax(prediction_weights, axis=1)

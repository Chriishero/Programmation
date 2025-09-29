import numpy as np
from sklearn.tree import DecisionTreeClassifier

class AdaBoostClassifier:
    def __init__(self, n_estimators=200):
        self.n_estimators = n_estimators

        self.w_ = None
        self.estimators_ = []
        self.estimators_perf_ = []

    def _train_estimators(self, X, y):
        m, n = X.shape
        self.w_ = np.ones(m) / m

        for i in range(self.n_estimators):
            model = DecisionTreeClassifier(max_depth=1)
            model.fit(X, y, sample_weight=self.w_)
            y_pred = model.predict(X)

            err = np.sum(self.w_ * (y_pred != y)) / np.sum(self.w_)
            perf = 1/2 * np.log((1 - err) / (err + 1e-16))

            self.estimators_.append(model)
            self.estimators_perf_.append(perf)

            self.w_ *= np.exp(-perf * y * y_pred)
            self.w_ /= np.sum(self.w_)

    def fit(self, X, y):
        X, y = np.array(X), np.array(y)
        self._train_estimators(X, y)

    def predict(self, X):
        X = np.array(X)
    
        strong_preds = np.zeros(X.shape[0])
        for model, perf in zip(self.estimators_, self.estimators_perf_):
            y_pred = model.predict(X)
            strong_preds += perf * y_pred

        return np.sign(strong_preds)

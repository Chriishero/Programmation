import numpy as np
from sklearn.tree import DecisionTreeClassifier

class AdaBoostClassifier:
    def __init__(self, n_estimators):
        self.n_estimators = n_estimators

        self.w_ = None
        self.models_ = []
        self.models_w_ = []

    def fit(self, X, y):
        X, y = np.array(X), np.array(y)
        m, n = X.shape

        self.w_ = np.ones(m) / m
        for i in range(self.n_estimators):
            model = DecisionTreeClassifier(depth=1)
            model.fit(X, y, sample_weight=self.w_)
            y_pred = model.predict(X)

            err = np.sum(self.w_ * (y_pred != y)) / np.sum(y)
            model_weight = 1/2 * np.log((1 - err) / (err + 1e-15))

            self.w_ *= np.exp(-model_weight * y * y_pred)
            self.w_ *= np.sum(self.w_)

            self.models_.append(model)
            self.models_w_.append(model_weight)

    def predict(self, X):
        X = np.array(X)

        strong_preds = np.zeros(X.shape[0])
        for model, weight in zip(self.models_, self.models_w_):
            strong_preds += weight * model.predict(X)
        return np.sign(strong_preds)
            
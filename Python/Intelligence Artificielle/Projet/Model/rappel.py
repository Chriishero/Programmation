import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression
from sklearn.metrics import r2_score
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeRegressor

X, y = make_regression(n_samples=500, n_features=10, noise=10, random_state=0)

class GradientBoostingRegressor:
    def __init__(self, n_iteration=200, learning_rate=0.1, loss='squared_error', subsample=0.6, early_stopping_rounds=10, validation_fraction=0.1):
        self.n_iteration = n_iteration
        self.learning_rate = learning_rate
        self.loss = loss
        self.subsample = subsample
        self.early_stopping_rounds = early_stopping_rounds
        self.validation_fraction = validation_fraction

        self.initial_prediction = None
        self.model_list = []

    def _gradient(self, y, y_pred):
        if self.loss == "squared_error":
            return (y - y_pred)

    def _subsamble(self, X, gradient):
        m, n = X.shape
        random_index = np.random.choice(len(X), int(m * self.subsample), replace=True)
        return X[random_index], gradient[random_index]

    def _gradient_descent(self, X, y):
        if self.validation_fraction and self.early_stopping_rounds:
            X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=self.validation_fraction, random_state=0)
        else:
            X_train, y_train = X, y
            X_val = y_val = None

        m, n = X_train.shape
        self.initial_prediction = 1/m * np.sum(y_train)
        y_pred = np.full(m, self.initial_prediction)
        gradient = self._gradient(y_train, y_pred)

        if X_val is not None:
            y_val_pred = np.full(X_val.shape[0], self.initial_prediction)
            best_val_score = float("-inf")
            best_iteration = 0

        for i in range(self.n_iteration):
            if self.subsample < 1.0:
                X_sub, gradient_sub = self._subsamble(X_train, gradient)
            else:
                X_sub, gradient_sub = X_train, gradient

            model = DecisionTreeRegressor(max_depth=3)
            model.fit(X_sub, gradient_sub)
            self.model_list.append(model)

            y_pred += self.learning_rate * model.predict(X_train)
            gradient = self._gradient(y_train, y_pred)

            if X_val is not None:
                y_val_pred = model.predict(X_val)
                score = r2_score(y_val, y_val_pred)

                if score > best_val_score:
                    best_val_score = score
                    best_iteration = i
                elif i - best_iteration >= self.early_stopping_rounds:
                    print(f"Early stopping at iteration {i}")
                    
    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self._gradient_descent(X, y)

    def predict(self, X):
        X = np.array(X)
        y_pred = np.full(X.shape[0], self.initial_prediction)
        for model in self.model_list:
            y_pred += self.learning_rate * model.predict(X)
        return y_pred

model = GradientBoostingRegressor()
model.fit(X, y)
y_pred = model.predict(X)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c='r')
plt.title(f'{r2_score(y, y_pred)}')
plt.show()
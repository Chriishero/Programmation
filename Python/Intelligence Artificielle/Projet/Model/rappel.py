import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification, make_regression
from sklearn.metrics import accuracy_score, r2_score
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import train_test_split

X, y = make_regression(n_samples=500, n_features=10, noise=30, random_state=0)

class GradientBoostingRegressor:
    def __init__(self, n_estimators=200, learning_rate=0.1, max_depth=3, loss='squared_loss', subsample=0.9, early_stopping_rounds=20, validation_fraction=0.1):
        self.n_estimators = n_estimators
        self.learning_rate = learning_rate
        self.max_depth = max_depth
        self.loss = loss
        self.subsample = subsample
        self.early_stopping_rounds = early_stopping_rounds
        self.validation_fraction = validation_fraction
        
        self.initial_prediction = None
        self.model_list = []

    def _gradient(self, y, y_pred):
        if self.loss == "squared_loss":
            return (y - y_pred)
        
    def _subsample(self, X, gradient):
        m, n = X.shape
        random_index = np.random.choice(m, int(m * self.subsample), replace=True)
        return X[random_index], gradient[random_index]
    
    def _gradient_descent(self, X, y):
        if self.early_stopping_rounds and self.validation_fraction:
            X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=self.validation_fraction, random_state=0)
        else:
            X_train, y_train = X, y
            X_val = y_val = None

        m, n = X_train.shape
        self.initial_prediction = 1/m * np.sum(y_train)
        y_pred = np.full(m, self.initial_prediction)
        gradient = self._gradient(y_train, y_pred)

        if X_val is not None:
            y_pred_val = np.full(X_val.shape[0], self.initial_prediction)
            best_score = float("-inf")
            best_iter = 0

        for i in range(self.n_estimators):
            if self.subsample < 1.0:
                X_sub, gradient_sub = self._subsample(X_train, gradient)
            else:
                X_sub, gradient_sub = X_train, gradient

            model = DecisionTreeRegressor(max_depth=self.max_depth)
            model.fit(X_sub, gradient_sub)
            self.model_list.append(model)

            y_pred = y_pred + self.learning_rate * model.predict(X_train)
            gradient = self._gradient(y_train, y_pred)

            if X_val is not None:
                y_pred_val = y_pred_val + self.learning_rate * model.predict(X_val)
                score = r2_score(y_val, y_pred_val)
                if score > best_score:
                    best_score = score
                    best_iter = i
                elif i - best_iter >= self.early_stopping_rounds:
                    print(f"Early stoppings at iteration {i}")
                    break

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self._gradient_descent(X, y)

    def predict(self, X):
        X = np.array(X)
        y_pred = np.full(X.shape[0], self.initial_prediction)
        for model in self.model_list:
            y_pred = y_pred + self.learning_rate * model.predict(X)
        return y_pred
    
model = GradientBoostingRegressor()
model.fit(X, y)
y_pred = model.predict(X)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c='r')
plt.title(f"{r2_score(y, y_pred)}")
plt.show()
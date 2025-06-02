import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression
from sklearn.metrics import r2_score
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import train_test_split

X, y = make_regression(n_samples=500, n_features=10, noise=10, random_state=0)

class GradientBoostingRegressor:
    def __init__(self, n_iterations=100, learning_rate=0.2, loss='squared_error', subsample=0.9, early_stopping_rounds=20, validation_fraction=0.1):
        self.n_iterations = n_iterations
        self.learning_rate = learning_rate
        self.loss = loss
        self.subsample = subsample # réduis la variance (bootstrap)
        self.early_stopping_rounds = early_stopping_rounds
        self.validation_fraction = validation_fraction
        
        self.initial_prediction = None # F0
        self.models_list = []

    def _gradient(self, y, y_pred):
        if self.loss == "squared_error":
            return (y - y_pred)
        if self.loss == "absolute_error":
            return np.sign(y - y_pred)
        
    def _subsample(self, X, gradient):
        m, n = X.shape
        random_index = np.random.choice(m, int(m * self.subsample), replace=True)
        return X[random_index], gradient[random_index]

    def _gradient_descent(self, X, y):
        if self.validation_fraction and self.early_stopping_rounds: # s'il y a early_stopping_rounds
            X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=self.validation_fraction, random_state=0)
        else:
            X_train, y_train = X, y
            X_val = y_val = None

        m, n = X_train.shape
        self.initial_prediction = 1/m * np.sum(y_train) # moyenne des valeurs réels (y)
        y_pred = np.full(m, self.initial_prediction, dtype=float) # prédictions initiales pour les exemples
        gradient = self._gradient(y_train, y_pred)

        if X_val is not None: # s'il y a early_stopping_rounds
            y_val_pred = np.full(X_val.shape[0], self.initial_prediction, dtype=float) # prédiction initiales sur le test de validation
            best_val_score = float("-inf")
            best_iteration = 0

        for i in range(self.n_iterations):
            if self.subsample < 1.0:
                X_subsample, gradient_subsample = self._subsample(X_train, gradient) # bootstrap
            else:
                X_subsample, gradient_subsample = X_train, gradient

            tree = DecisionTreeRegressor(max_depth=3)
            tree.fit(X_subsample, gradient_subsample)
            self.models_list.append(tree)

            y_pred = y_pred + self.learning_rate * tree.predict(X_train) # fi := fi-1 + alpha * Fi
            gradient = self._gradient(y_train, y_pred)

            if X_val is not None: # s'il y a early_stopping_rounds
                y_val_pred = y_val_pred + self.learning_rate * model.predict(X_val) # fi := fi-1 + alpha * Fi
                score = r2_score(y_val, y_val_pred)

                if score > best_val_score:
                    best_val_score = score
                    best_iteration = i
                elif i - best_iteration >= self.early_stopping_rounds:
                    print(f'Early stoppping at iteration {i}')
                    break

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self._gradient_descent(X, y)

    def predict(self, X):
        X = np.array(X)
        y_pred = np.full(X.shape[0], self.initial_prediction, dtype=float) # prédictions initiales
        for tree in self.models_list:
            y_pred = y_pred + self.learning_rate * tree.predict(X) # fi := fi-1 + alpha * Fi
        return y_pred
    
model = GradientBoostingRegressor()
model.fit(X, y)
y_pred = model.predict(X)

plt.figure()
plt.scatter(y, y_pred)
plt.plot([y.min(), y.max()], [y.min(), y.max()], 'r--')
plt.title(f'{r2_score(y, y_pred)}')
plt.show()
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_friedman1, make_regression
from sklearn.metrics import r2_score
from sklearn.model_selection import train_test_split

class TreeNode:
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, value=None):
        self.feature_index = feature_index
        self.threshold = threshold
        self.left = left
        self.right = right
        self.value = value

class DecisionTreeRegressor:
    def __init__(self, max_features, max_depth, min_samples_leaf, min_samples_split, reg_lambda, reg_gamma):
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.reg_lambda = reg_lambda
        self.reg_gamma = reg_gamma

        self.tree = None

    def _gain_function(self, G_left, G_right, H_left, H_right):
        return 1/2 * (G_left**2 / (H_left + self.reg_lambda) + G_right**2 / (H_right + self.reg_lambda) 
                      - (G_left + G_right)**2 / (H_left + H_right + self.reg_lambda)) - self.reg_gamma
    
    def _split_function(self, X, gradient, hessian):
        m, n = X.shape
        best_split = None
        best_gain = float('-inf')
        feature_indices = np.arange(n)

        if isinstance(self.max_features, int):
            feature_indices = np.random.choice(n, self.max_features, replace=False)
        elif self.max_features == 'sqrt':
            feature_indices = np.random.choice(n, int(np.sqrt(n)), replace=False)

        for feature_index in feature_indices:
            thresholds = np.unique(X[:, feature_index])
            for threshold in thresholds:
                left_mask = X[:, feature_index] < threshold
                right_mask = ~left_mask

                if len(gradient[left_mask]) < self.min_samples_leaf or len(gradient[right_mask]) < self.min_samples_leaf:
                    continue
                if len(gradient[left_mask]) < self.min_samples_split or len(gradient[right_mask]) < self.min_samples_split:
                    continue

                G_left = np.sum(gradient[left_mask])
                G_right = np.sum(gradient[right_mask])
                H_left = np.sum(hessian[left_mask])
                H_right = np.sum(hessian[right_mask])
                gain = self._gain_function(G_left, G_right, H_left, H_right)

                if gain > best_gain:
                    best_gain = gain
                    best_split = feature_index, threshold

        return best_split
    
    def _tree_function(self, X, gradient, hessian, depth=0):
        def _leaf_values():
            G = np.sum(gradient)
            H = np.sum(hessian)
            return TreeNode(value=-G / (H + self.reg_lambda))
        
        if self.max_depth is not None and self.max_depth <= depth:
            return _leaf_values()
        
        split = self._split_function(X, gradient, hessian)
        if split is None:
            return _leaf_values()
        
        feature_index, threshold = split
        left_mask = X[:, feature_index] < threshold
        right_mask = ~left_mask

        if len(gradient[left_mask]) == 0 or len(gradient[right_mask]) == 0:
            return _leaf_values()
        
        left_tree = self._tree_function(X[left_mask], gradient[left_mask], hessian[left_mask], depth+1)
        right_tree = self._tree_function(X[right_mask], gradient[right_mask], hessian[right_mask], depth+1)

        return TreeNode(feature_index, threshold, left_tree, right_tree)
    
    def _predict_samples(self, x, tree):
        if tree.value is not None:
            return tree.value
        if x[tree.feature_index] < tree.threshold:
            return self._predict_samples(x, tree.left)
        else:
            return self._predict_samples(x, tree.right)
        
    def fit(self, X, gradient, hessian):
        self.tree = self._tree_function(np.array(X), np.array(gradient), np.array(hessian))

    def predict(self, X):
        X = np.array(X)
        return np.array([self._predict_samples(x, self.tree) for x in X])
    
class XGBoostRegressor:
    def __init__(self, n_estimators=100, learning_rate=0.2, max_features="sqrt", max_depth=3, min_samples_leaf=10, min_samples_split=5,
                 reg_lambda=1.0, reg_gamma=0.0, subsample=0.9, loss='mean_squared', early_stopping_rounds=20, validation_fraction=0.1):
        self.n_estimators = n_estimators
        self.learning_rate = learning_rate
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.reg_lambda = reg_lambda
        self.reg_gamma = reg_gamma
        self.subsample = subsample # réduis la variance (bootstrap)
        self.loss = loss
        self.early_stopping_rounds = early_stopping_rounds
        self.validation_fraction = validation_fraction

        self.initial_prediction = None # F0
        self.model_list = []

    def _compute_gradient_hessian(self, y, y_pred):
        if self.loss == 'mean_squared':
            gradient = y_pred - y
            hessian = np.ones_like(y)
            return gradient, hessian

    def _subsample_function(self, X, gradient, hessian):
        m, n = X.shape
        random_index = np.random.choice(m, int(m * self.subsample), replace=False)
        return X[random_index], gradient[random_index], hessian[random_index]

    def _gradient_descent(self, X, y):
        if self.early_stopping_rounds and self.validation_fraction: # s'il y a early_stopping_rounds
            X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=self.validation_fraction, random_state=0)
        else:
            X_train, y_train = X, y
            X_val = y_val = None

        m, n = X_train.shape
        self.initial_prediction = 1/m * np.sum(y_train) # moyenne des valeurs réels (y)
        y_pred = np.full(m, self.initial_prediction) # prédictions initiales pour les exemples

        if X_val is not None: # s'il y a early_stopping_rounds
            pred_val = np.full(X_val.shape[0], self.initial_prediction) # prédiction initiales sur le test de validation
            best_score = float("-inf")
            best_iter = None

        for i in range(self.n_estimators):
            gradient, hessian = self._compute_gradient_hessian(y_pred, y_train)

            X_sub, grad_sub, hess_sub = self._subsample_function(X_train, gradient, hessian) # bootstrap
            model = DecisionTreeRegressor(self.max_features, self.max_depth, self.min_samples_leaf, self.min_samples_split,
                                            self.reg_lambda, self.reg_gamma)
            model.fit(X_sub, -grad_sub, hess_sub)
            self.model_list.append(model)
            y_pred += self.learning_rate * model.predict(X_train) # fi := fi-1 + alpha * Fi
            
            if X_val is not None: # s'il y a early_stopping_rounds
                pred_val += self.learning_rate * model.predict(X_val) # fi := fi-1 + alpha * Fi
                score = r2_score(y_val, pred_val)
                if score > best_score:
                    best_score = score
                    best_iter = i
                elif i - best_iter >= self.early_stopping_rounds:
                    print(f'break at {i}')
                    break

    def fit(self, X, y):
        self._gradient_descent(np.array(X), np.array(y))

    def predict(self, X):
        X = np.array(X)
        y_pred = np.full(X.shape[0], self.initial_prediction)
        for model in self.model_list:
            y_pred += self.learning_rate * model.predict(X) # fi := fi-1 + alpha * Fi
        return y_pred

X, y = make_friedman1(n_samples=1000, n_features=10, noise=1, random_state=0)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, random_state=0)

model = XGBoostRegressor()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

plt.figure()
plt.scatter(y_test, y_pred)
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], color='r')
plt.title(f'{r2_score(y_test, y_pred)}')
plt.show()
import numpy as np
from sklearn.metrics import r2_score, accuracy_score
from sklearn.model_selection import train_test_split

class TreeNode:
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, value=None):
        self.feature_index = feature_index
        self.threshold = threshold
        self.left = left
        self.right = right
        self.value = value

class DecisionTreeRegressor:
    def __init__(self, max_features=None, max_depth=None, min_samples_leaf=None, min_samples_split=None,
                  reg_lambda=None, reg_gamma=None):
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.reg_lambda = reg_lambda
        self.reg_gamma = reg_gamma
    
    def _gain_function(self, G_left, G_right, H_left, H_right):
        return 1/2 * (G_left**2 / (H_left + self.reg_lambda) + G_right**2 / (H_right + self.reg_lambda) - 
                      (G_left + G_right)**2 / (H_left + H_right + self.reg_lambda)) - self.reg_gamma
    
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
        def _leaf_value():
            G = np.sum(gradient)
            H = np.sum(hessian)
            return TreeNode(value=-G / (H + self.reg_lambda))
        
        if self.max_depth is not None and self.max_depth <= depth:
            return _leaf_value()
        
        split = self._split_function(X, gradient, hessian)
        if split is None:
            return _leaf_value()
        
        feature_index, threshold = split
        left_mask = X[:, feature_index] < threshold
        right_mask = ~left_mask

        if len(gradient[left_mask]) == 0 or len(gradient[right_mask]) == 0:
            return _leaf_value()
        
        left_tree = self._tree_function(X[left_mask], gradient[left_mask], hessian[left_mask], depth+1)
        right_tree = self._tree_function(X[right_mask], gradient[right_mask], hessian[right_mask], depth+1)

        return TreeNode(feature_index, threshold, left_tree, right_tree)
    
    def _predict_sample(self, x, tree):
        if tree.value is not None:
            return tree.value
        if x[tree.feature_index] < tree.threshold:
            return self._predict_sample(x, tree.left)
        else:
            return self._predict_sample(x, tree.right)
        
    def fit(self, X, gradient, hessian):
        self.tree = self._tree_function(np.array(X), np.array(gradient), np.array(hessian))

    def predict(self, X):
        return np.array([self._predict_sample(x, self.tree) for x in np.array(X)])
    
class XGBoostRegressor:
    def __init__(self, n_estimators=100, learning_rate=0.2, max_features='sqrt', max_depth=3, 
                 min_samples_leaf=10, min_samples_split=5, reg_lambda=1.0, reg_gamma=0.0, 
                 subsample=0.9, loss='log_loss', early_stopping_rounds=20, validation_fraction=0.1):
        self.n_estimators = n_estimators
        self.learning_rate = learning_rate
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.reg_lambda = reg_lambda
        self.reg_gamma = reg_gamma
        self.subsample = subsample
        self.loss = loss
        self.early_stopping_rounds = early_stopping_rounds
        self.validation_fraction = validation_fraction

        self.initial_prediction = None
        self.model_list = []

    def _gradient_hessian(self, y, y_pred):
        if self.loss == 'log_loss':
            return y - y_pred, np.ones_like(y)
        
    def _subsample_function(self, X, gradient, hessian):
        random_index = np.random.choice(len(X), int(len(X * self.subsample)), replace=False)
        return X[random_index], gradient[random_index], hessian[random_index]

    def _gradient_descent(self, X, y):
        if self.early_stopping_rounds is not None and self.validation_fraction is not None:
            X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=self.validation_fraction, random_state=0)
        else:
            X_train, y_train = X, y
            X_val = y_val = None

        m, n = X_train.shape
        self.initial_prediction = 1/m * np.sum(y_train)
        y_pred = np.full(m, self.initial_prediction)

        if self.early_stopping_rounds is not None and self.validation_fraction is not None:
            val_pred = np.full(X_val.shape[0], self.initial_prediction)
            best_score = float('-inf')
            best_i = None

        for i in range(self.n_estimators):
            gradient, hessian = self._gradient_hessian(y_train, y_pred)
            X_sub, grad_sub, hess_sub = self._subsample_function(X_train, gradient, hessian)
            model = DecisionTreeRegressor(self.max_features, self.max_depth, self.min_samples_leaf, self.min_samples_split,
                                            self.reg_lambda, self.reg_gamma)
            model.fit(X_sub, -grad_sub, hess_sub)
            self.model_list.append(model)
            y_pred += self.learning_rate * model.predict(X_train)

            if self.early_stopping_rounds is not None and self.validation_fraction is not None:
                val_pred += self.learning_rate * model.predict(X_val)
                score = r2_score(y_val, val_pred)
                if score > best_score:
                    best_score = score
                    best_i = i
                elif i - best_i >= self.early_stopping_rounds:
                    print(f'stop at {i}')
                    break

    def fit(self, X, y):
        self._gradient_descent(np.array(X), np.array(y))

    def predict(self, X):
        X = np.array(X)
        y_pred = np.full(X.shape[0], self.initial_prediction)
        for model in self.model_list:
            y_pred += self.learning_rate * model.predict(X)
        return y_pred
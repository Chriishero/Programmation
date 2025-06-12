import numpy as np
from sklearn.metrics import accuracy_score, r2_score
from sklearn.model_selection import train_test_split

class TreeNode:
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, value=None):
        self.feature_index = feature_index
        self.threshold = threshold
        self.left = left
        self.right = right
        self.value = value

class DecisionTreeRegressor:
    def __init__(self, max_features=None, max_depth=None, min_samples_leaf=None, min_samples_split=None, reg_lambda=None, reg_gamma=None):
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.reg_lambda = reg_lambda
        self.reg_gamma = reg_gamma

        self.tree = None

    def _loss_function(self, y):
        m = len(y)
        means = 1/m * np.sum(y)
        return 1/m * np.sum((y - means)**2)
    
    def _gain_function(self, G_left, G_right, H_left, H_right):
        return 1/2 * (G_left**2 / (H_left + self.reg_lambda) + G_right**2 / (H_right + self.reg_lambda)
                    - (G_left + G_right)**2 / (H_left + H_right + self.reg_lambda)) - self.reg_gamma    
    
    def _split_function(self, X, grad, hess):
        m, n = X.shape
        best_split = None
        best_gain = float("-inf")
        indices = np.arange(n)

        if isinstance(self.max_features, int):
            indices = np.random.choice(n, self.max_features, replace=False)
        elif self.max_features == 'sqrt':
            indices = np.random.choice(n, int(np.sqrt(n)), replace=False)

        for feature_index in indices:
            thresholds = np.unique(X[:, feature_index])
            for threshold in thresholds:
                left_mask = X[:, feature_index] < threshold
                right_mask = ~left_mask

                if self.min_samples_leaf is not None and len(grad[left_mask]) < self.min_samples_leaf or len(grad[right_mask]) < self.min_samples_leaf:
                    continue
                if self.min_samples_split is not None and len(grad[left_mask]) < self.min_samples_split or len(grad[right_mask]) < self.min_samples_split:
                    continue

                G_left = np.sum(grad[left_mask])
                G_right = np.sum(grad[right_mask])
                H_left = np.sum(hess[left_mask])
                H_right = np.sum(hess[right_mask])
                gain = self._gain_function(G_left, G_right, H_left, H_right)
                if gain > best_gain:
                    best_gain = gain
                    best_split = feature_index, threshold

        return best_split
    
    def _tree_function(self, X, grad, hess, depth=0):
        def _leaf_values():
            G = np.sum(grad)
            H = np.sum(hess)
            return TreeNode(value=-G / (H + self.reg_lambda))
        
        if self.max_depth is not None and self.max_depth < depth:
            return _leaf_values()
        
        split = self._split_function(X, grad, hess)
        if split is None:
            return _leaf_values()
        
        feature_index, threshold = split
        left_mask = X[:, feature_index] < threshold
        right_mask = ~left_mask

        if len(grad[left_mask]) == 0 or len(grad[right_mask]) == 0:
            return _leaf_values()
        
        left_tree = self._tree_function(X[left_mask], grad[left_mask], hess[left_mask], depth+1)
        right_tree = self._tree_function(X[right_mask], grad[right_mask], hess[right_mask], depth+1)

        return TreeNode(feature_index, threshold, left_tree, right_tree)
    
    def _predict_sample(self, x, tree):
        if tree.value is not None:
            return tree.value
        if x[tree.feature_index] < tree.threshold:
            return self._predict_sample(x, tree.left)
        else:
            return self._predict_sample(x, tree.right)
        
    def fit(self, X, grad, hess):
        self.tree = self._tree_function(np.array(X), np.array(grad), np.array(hess))

    def predict(self, X):
        return np.array([self._predict_sample(x, self.tree) for x in X])
    
class XGBoostClassifier:
    def __init__(self, n_estimators=100, learning_rate=0.2, max_features='sqrt', max_depth=3, min_samples_leaf=10, min_samples_split=5,
                 reg_lambda=1.0, reg_gamma=0.0, subsample=0.9, loss='log_loss', early_stopping_rounds=20, validation_fraction=0.1):
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

        self.n_classes = 0
        self.model_list = []

    def _softmax(self, logits):
        exp = np.exp(logits - np.max(logits, axis=1, keepdims=True))
        return exp / np.sum(exp, axis=1, keepdims=True)
    
    def _gradient_hessian(self, proba, y_onehot):
        if self.loss == "log_loss":
            return proba - y_onehot, proba * (1 - proba)

    def _subsample(self, X, gradient, hessian):
        m, n = X.shape
        random_index = np.random.choice(m, int(m * self.subsample), replace=True)
        return X[random_index], gradient[random_index], hessian[random_index]
    
    def _gradient_descent(self, X, y):
        if self.early_stopping_rounds is not None and self.validation_fraction is not None:
            X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=self.validation_fraction, random_state=0)
            self.n_classes = np.max(y_train) + 1
            val_logits = np.zeros((X_val.shape[0], self.n_classes))
            best_score = float("-inf")
            best_i = None

        else:
            X_train, y_train = X, y
            X_val = y_val = None

        m, n = X_train.shape
        logits = np.zeros((m, self.n_classes))
        y_onehot = np.eye(self.n_classes)[y_train]

        self.model_list = [[] for _ in range(self.n_classes)]

        for i in range(self.n_estimators):
            proba = self._softmax(logits)
            gradient, hessian = self._gradient_hessian(proba, y_onehot)
            for k in range(self.n_classes):
                X_sub, grad_sub, hess_sub = self._subsample(X_train, gradient[:, k], hessian[:, k])
                model = DecisionTreeRegressor(self.max_features, self.max_depth, self.min_samples_leaf, self.min_samples_split,
                                              self.reg_lambda, self.reg_gamma)
                model.fit(X_sub, grad_sub, hess_sub)
                self.model_list[k].append(model)
                logits[:, k] += self.learning_rate * model.predict(X_train)
            if self.early_stopping_rounds is not None and self.validation_fraction is not None:
                for k in range(self.n_classes):
                    val_logits[:, k] += self.learning_rate * self.model_list[k][-1].predict(X_val)
                pred_val = np.argmax(self._softmax(val_logits), axis=1)
                score = accuracy_score(y_val, pred_val)
                if score > best_score:
                    best_score = score
                    best_i = i
                elif i - best_i >= self.early_stopping_rounds:
                    print(f"early stopping at {i}")
                    break
    
    def fit(self, X, y):
        self._gradient_descent(np.array(X), np.array(y))

    def predict(self, X):
        X = np.array(X)
        logits = np.zeros((X.shape[0], self.n_classes))
        for k in range(self.n_classes):
            for model in self.model_list[k]:
                logits[:, k] += self.learning_rate * model.predict(X)
        return np.argmax(self._softmax(logits), axis=1)

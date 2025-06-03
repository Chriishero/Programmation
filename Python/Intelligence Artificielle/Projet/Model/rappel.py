import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification, make_regression
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
    def __init__(self, max_features, max_depth, min_samples_leaf, min_samples_split):
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split

        self.tree = None

    def _mean_squared_loss(self, y):
        m, n = X.shape
        means = 1/m * np.sum(y)
        return 1/m * np.sum((y - means)**2)
    
    def _gain(self, y, y_left, y_right):
        m, n = X.shape
        node_loss = self._mean_squared_loss(y)
        left_loss = self._mean_squared_loss(y_left)
        right_loss = self._mean_squared_loss(y_right)
        return node_loss - (len(y_left) / m * left_loss + len(y_right) / m * right_loss)
    
    def _split(self, X, y):
        m, n = X.shape
        best_split = None
        best_gain = float("-inf")
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
                y_left, y_right = y[left_mask], y[right_mask]

                if len(y_left) < self.min_samples_leaf or len(y_right) < self.min_samples_leaf:
                    continue
                if len(y_left) < self.min_samples_split or len(y_right) < self.min_samples_split:
                    continue

                gain = self._gain(y, y_left, y_right)
                if gain > best_gain:
                    best_gain = gain
                    best_split = feature_index, threshold

        return best_split
    
    def _tree(self, X, y, depth=0):
        def _mean():
            return TreeNode(value=1/len(y) * np.sum(y))
        if self.max_depth is not None and self.max_depth <= depth:
            return _mean()
        
        split = self._split(X, y)
        if split is None:
            return _mean()
        
        feature_index, threshold = split
        left_mask = X[:, feature_index] < threshold
        right_mask = ~left_mask
        if len(y[left_mask]) == 0 or len(y[right_mask]) == 0:
            return _mean()
        
        left_tree = self._tree(X[left_mask], y[left_mask], depth+1)
        right_tree = self._tree(X[right_mask], y[right_mask], depth+1)

        return TreeNode(feature_index, threshold, left_tree, right_tree)
    
    def _predict_sample(self, x, tree):
        if tree.value is not None:
            return tree.value
        elif x[tree.feature_index] < tree.threshold:
            return self._predict_sample(x, tree.left)
        else:
            return self._predict_sample(x, tree.right)
        
    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self.tree = self._tree(X, y)

    def predict(self, X):
        X = np.array(X)
        return np.array([self._predict_sample(x, self.tree) for x in X])
    
class GradientBoostingClassifier:
    def __init__(self, n_estimators=200, learning_rate=0.1, max_features='sqrt', max_depth=5, min_samples_leaf=10, min_samples_split=5, loss='log_loss', subsample=0.9, early_stopping_rounds=20, validation_fraction=0.1):
        self.n_estimators = n_estimators
        self.learning_rate = learning_rate
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.loss = loss
        self.subsample = subsample
        self.early_stopping_rounds = early_stopping_rounds
        self.validation_fraction = validation_fraction

        self.n_classes = None
        self.model_list = []

    def _softmax(self, logits):
        exp = np.exp(logits - np.max(logits, axis=1, keepdims=True))
        return exp / np.sum(exp, axis=1, keepdims=True)

    def _gradient(self, y_onehot, proba):
        if self.loss == "log_loss":
            return proba - y_onehot
        
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
        self.n_classes = np.max(y_train) + 1
        logits = np.zeros((m, self.n_classes))
        y_onehot = np.eye(self.n_classes)[y_train]

        if X_val is not None:
            val_logits = np.zeros((X_val.shape[0], self.n_classes))
            best_score = float("-inf")
            best_iter = 0

        self.model_list = [[] for _ in range(self.n_classes)]
        for i in range(self.n_estimators):
            proba = self._softmax(logits)
            gradient = self._gradient(y_onehot, proba)
            for k in range(self.n_classes):
                if self.subsample < 1.0:
                    X_sub, gradient_sub = self._subsample(X_train, gradient[:, k])
                else:
                    X_sub, gradient_sub = X_train, gradient

                model = DecisionTreeRegressor(self.max_features, self.max_depth, self.min_samples_leaf, self.min_samples_split)
                model.fit(X_sub, -gradient_sub)
                self.model_list[k].append(model)
                
                logits[:, k] += self.learning_rate * model.predict(X_train)

            if X_val is not None:
                for k in range(self.n_classes):
                    val_logits[:, k] += self.learning_rate * self.model_list[k][-1].predict(X_val)
                val_pred = np.argmax(self._softmax(val_logits), axis=1)
                score = accuracy_score(y_val, val_pred)
                if score > best_score:
                    best_score = score
                    best_iter = i
                elif i - best_iter >= self.early_stopping_rounds:
                    print(f"Early stopping at {i}")
                    break

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self._gradient_descent(X, y)

    def predict(self, X):
        X = np.array(X)
        logits = np.zeros((len(X), self.n_classes))
        for k in range(self.n_classes):
            for model in self.model_list[k]:
                logits[:, k] += self.learning_rate * model.predict(X)

        return np.argmax(self._softmax(logits), axis=1)


X, y = make_classification(n_samples=500, n_features=10, n_informative=2, n_clusters_per_class=1, n_classes=4, random_state=0)
model = GradientBoostingClassifier()
model.fit(X, y)
y_pred = model.predict(X)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c='r')
plt.title(f'{accuracy_score(y, y_pred)}')
plt.show()
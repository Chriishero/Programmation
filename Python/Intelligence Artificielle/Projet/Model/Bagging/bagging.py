import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.metrics import accuracy_score

X, y = make_classification(n_features=10, n_samples=500, n_informative=2, n_clusters_per_class=1, n_classes=4, random_state=0)

class TreeNode:
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, value=None):
        self.feature_index = feature_index
        self.threshold = threshold
        self.left = left
        self.right = right
        self.value = value

class DecisionTree:
    def __init__(self, max_depth=None, min_sample_leaf=10, min_sample_split=5):
        self.max_depth = max_depth
        self.min_sample_leaf = min_sample_leaf
        self.min_sample_split = min_sample_split
        self.tree = None

    def _entropy(self, y):
        m = len(y)
        _, counts = np.unique(y, return_counts=True)
        probabilities = 1/m * counts
        return -np.sum(probabilities * np.log2(probabilities + 1e-15))
    
    def _gain_function(self, y, y_left, y_right):
        m = len(y)
        entropy_node = self._entropy(y)
        entropy_left = self._entropy(y_left)
        entropy_right = self._entropy(y_right)
        return entropy_node - (len(y_left) / m * entropy_left + len(y_right) / m * entropy_right)
    
    def _split_function(self, X, y):
        m, n = X.shape
        best_split = None
        best_gain = float("-inf")
        for feature_index in range(n):
            thresholds = np.unique(X[:, feature_index])
            for threshold in thresholds:
                left_mask = X[:, feature_index] < threshold
                right_mask = ~left_mask
                y_left, y_right = y[left_mask], y[right_mask]

                if len(y_left) < self.min_sample_leaf or len(y_right) < self.min_sample_leaf:
                    continue
                if len(y_left) < self.min_sample_split or len(y_right) < self.min_sample_split:
                    continue

                gain = self._gain_function(y, y_left, y_right)
                if gain > best_gain:
                    gain = best_gain
                    best_split = feature_index, threshold

        return best_split
    
    def _build_tree(self, X, y, depth=0):
        if len(set(y)) == 1:
            return TreeNode(value=y[0])
        
        def _majority_class(y):
            majority_class = np.bincount(y).argmax()
            return TreeNode(value=majority_class)
        
        if self.max_depth is not None and self.max_depth <= depth:
            return _majority_class(y)
        
        best_split = self._split_function(X, y)
        if best_split is None:
            return _majority_class(y)
        
        feature_index, threshold = best_split
        left_mask = X[:, feature_index] < threshold
        right_mask = ~left_mask
        
        if len(y[left_mask]) == 0 or len(y[right_mask]) == 0:
            return _majority_class(y)
        
        left_tree = self._build_tree(X[left_mask], y[left_mask], depth+1)
        right_tree = self._build_tree(X[right_mask], y[right_mask], depth+1)

        return TreeNode(feature_index, threshold, left_tree, right_tree)
    
    def _predict_sample(self, x, tree):
        if tree.value is not None:
            return tree.value
        if x[tree.feature_index] < tree.threshold:
            return self._predict_sample(x, tree.left)
        else:
            return self._predict_sample(x, tree.right)
        
    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self.tree = self._build_tree(X, y)
        return self

    def predict(self, X):
        X = np.array(X)
        return np.array([self._predict_sample(x, self.tree) for x in X])

class Bagging:
    def __init__(self, model=None, n_estimators=10):
        self.model = model
        self.n_estimators = n_estimators
        self.model_list = []

    def _bootstrap(self, X, y):
        random_index = np.random.choice(len(X), size=len(X), replace=True)
        return X[random_index], y[random_index]

    def _train_estimator(self, X, y):
        for i in range(self.n_estimators):
            X_boostrap, y_bootstrap = self._bootstrap(X, y)
            model = self.model
            model.fit(X_boostrap, y_bootstrap)
            self.model_list.append(model)

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self._train_estimator(X, y)

    def predict(self, X):
        X = np.array(X)
        predictions_list = np.array([model.predict(X) for model in self.model_list])

        n_samples = predictions_list.shape[1]
        majority_votes = []
        for i in range(n_samples):
            values, counts = np.unique(predictions_list[:, i], return_counts=True)
            majority_vote = values[np.argmax(counts)]
            majority_votes.append(majority_vote)

        return np.array(majority_votes)

model = Bagging(model=DecisionTree())
model.fit(X, y)
y_pred = model.predict(X)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c='r')
plt.title(f"{accuracy_score(y, y_pred)}")
plt.show()

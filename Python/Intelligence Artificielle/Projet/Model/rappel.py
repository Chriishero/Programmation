import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.metrics import accuracy_score, r2_score

X, y = make_classification(n_samples=500, n_features=10, n_informative=8, n_classes=4, random_state=0)

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
        return np.sum(probabilities * np.log2(probabilities + 1e-15))
    
    def _gain_function(self, y, y_left, y_right):
        m = len(y)
        entropy_left = self._entropy(y_left)
        entropy_right = self._entropy(y_right)
        entropy_set = self._entropy(y)

        return entropy_set - (len(y_left) / m * entropy_left + len(y_right) / m * entropy_right)
    
    def _best_split(self, X, y):
        m, n = X.shape
        best_gain = float("-inf")
        best_split = None
        
        for feature_index in range(n):
            thresholds = np.unique(X[:, feature_index])
            for threshold in thresholds:
                left_mask = X[:, feature_index] < threshold
                right_mask = ~left_mask
                y_left, y_right = y[left_mask], y[right_mask]

                if len(y) < self.min_sample_leaf or len(y) < self.min_sample_leaf:
                    continue
                if len(y) < self.min_sample_split or len(y) < self.min_sample_split:
                    continue

                gain = self._gain_function(y, y_left, y_right)
                if gain > best_gain:
                    best_gain = gain
                    best_split = (feature_index, threshold)

        return best_split
     
    def _build_tree(self, X, y, depth=0):
        if len(set(y)) == 1:
            return TreeNode(value=y[0])
        
        if self.max_depth is not None and depth >= self.max_depth:
            majority_class = np.bincount(y).argmax(y)
            return TreeNode(value=majority_class)
        
        best_split = self._best_split(X, y)

        if best_split is None:
            majority_class = np.bincount(y).argmax(y)
            return TreeNode(value=majority_class)
        
        feature, threshold = best_split
        left_mask = X[:, feature] < threshold
        right_mask = ~left_mask

        if len(y[left_mask]) == 0 or len(y[right_mask]) == 0:
            majority_class = np.bincount(y).argmax(y)
            return TreeNode(value=majority_class)
        
        left_tree = self._build_tree(X[left_mask], y[left_mask], depth+1)
        right_tree = self._build_tree(X[right_mask], y[right_mask], depth+1)

        return TreeNode(feature_index=feature, threshold=threshold, left=left_tree, right=right_tree)

model = DecisionTree()
model.fit(X, y)
y_pred = model.predict(X)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c='r')
plt.title(f"{accuracy_score(y, y_pred)}")
plt.show()
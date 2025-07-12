import numpy as np

class TreeNode:
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, value=None):
        self.feature_index = feature_index
        self.threshold = threshold
        self.left = left
        self.right = right
        self.value = value

class DecisionTreeClassifier:
    def __init__(self, max_features, max_depth, min_samples_leaf, min_samples_split):
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split

        self.tree = None

    def _loss_function(self, y):
        m = len(y)
        _, counts = np.unique(y, return_counts=True)
        proba = 1/m * counts
        return -np.sum(proba * np.log2(proba + 1e-15))
    
    def _gain_function(self, y, y_left, y_right):
        m = len(y)
        loss_node = self._loss_function(y)
        loss_left = self._loss_function(y_left)
        loss_right = self._loss_function(y_right)
        return loss_node - (len(y_left) / m * loss_left + len(y_right) / m * loss_right)
    
    def _split_function(self, X, y):
        m, n = X.shape
        best_split = None
        best_gain = float("-inf")
        indices = np.arange(n)

        if isinstance(self.max_features, int):
            indices = np.random.choice(n, self.max_features, replace=False)
        elif self.max_features == 'sqrt':
            indices = np.random.choice(n, int(np.sqrt(n)), replace=False)
        elif self.max_features == 'log2':
            indices = np.random.choice(n, int(np.log2(n)), replace=False)

        for feature_index in indices:
            thresholds = np.unique(X[:, feature_index])
            for threshold in thresholds:
                left_mask = X[:, feature_index] < threshold
                right_mask = ~left_mask

                if self.min_samples_leaf is not None and (len(y[left_mask]) < self.min_samples_leaf or
                                                          len(y[right_mask]) < self.min_samples_leaf):
                    continue
                if self.min_samples_split is not None and (len(y[left_mask]) < self.min_samples_split or
                                                           len(y[right_mask]) < self.min_samples_split):
                    continue

                gain = self._gain_function(y, y[left_mask], y[right_mask])
                if gain > best_gain:
                    best_gain = gain
                    best_split = feature_index, threshold
        return best_split
    
    def _tree_function(self, X, y, depth=0):
        if len(set(y)) == 0:
            return TreeNode(value=y[0])
        
        def _leaf_value():
            return TreeNode(value=np.bincount(y).argmax())
        
        if self.max_depth is not None and self.max_depth <= depth:
            return _leaf_value()
        
        split = self._split_function(X, y)
        if split is None:
            return _leaf_value()
        
        feature_index, threshold = split
        left_mask = X[:, feature_index] < threshold
        right_mask = ~left_mask

        if len(y[left_mask]) == 0 or len(y[right_mask]) == 0:
            return _leaf_value()
        
        left_tree = self._tree_function(X[left_mask], y[left_mask], depth+1)
        right_tree = self._tree_function(X[right_mask], y[right_mask], depth+1)

        return TreeNode(feature_index, threshold, left_tree, right_tree)
    
    def _predict_sample(self, x, tree):
        if tree.value is not None:
            return tree.value
        elif x[tree.feature_index] < tree.threshold:
            return self._predict_sample(x, tree.left)
        else:
            return self._predict_sample(x, tree.right)
        
    def fit(self, X, y):
        X, y = np.array(X), np.array(y)
        self.tree = self._tree_function(X, y)

    def predict(self, X):
        return np.array([self._predict_sample(x, self.tree) for x in np.array(X)])
    
class RandomForestClassifier:
    def __init__(self, n_estimators=100, max_features='sqrt', max_depth=5, min_samples_leaf=10, min_samples_split=5):
        self.n_estimators = n_estimators
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf 
        self.min_samples_split = min_samples_split

        self.model_list = []

    def _bootstrap_sample(self, X, y):
        m, n = X.shape
        random_index = np.random.choice(m, m, replace=True)
        return X[random_index], y[random_index]
    
    def _train_estimators(self, X, y):
        for i in range(self.n_estimators):
            X_boot, y_boot = self._bootstrap_sample(X, y)
            model = DecisionTreeClassifier(self.max_features, self.max_depth, self.min_samples_leaf, self.min_samples_split)
            model.fit(X_boot, y_boot)
            self.model_list.append(model)

    def fit(self, X, y):
        X, y = np.array(X), np.array(y)
        self._train_estimators(X, y)

    def predict(self, X):
        X = np.array(X)
        predictions_list = np.array([model.predict(X) for model in self.model_list])

        majority_votes = []
        for i in range(X.shape[0]):
            classes, counts = np.unique(predictions_list[:, i], return_counts=True)
            majority_vote = classes[np.argmax(counts)]
            majority_votes.append(majority_vote)
        return np.array(majority_votes)

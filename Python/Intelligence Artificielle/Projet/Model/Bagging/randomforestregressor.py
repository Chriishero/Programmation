import numpy as np

class TreeNode:
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, value=None):
        self.feature_index = feature_index  # j
        self.threshold = threshold          # theta
        self.left = left                    # sous-arbre gauche (xj < theta)
        self.right = right                  # sous-arbre droit (xj >= theta)
        self.value = value                  # prédiction w_j si feuille

class DecisionTreeRegressor:
    def __init__(self, max_features="sqrt", max_depth=None, min_samples_leaf=10, min_samples_split=5, verbosity=0):
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.verbosity = verbosity
        self.tree = None

    def _mean_squared_error(self, y):
        m = len(y)
        means = 1/m * np.sum(y) # moyenne des prédictions
        return 1/m * np.sum((y - means)**2)
    
    def _gain(self, y, left_y, right_y):
        m = len(y)
        error_left = self._mean_squared_error(left_y) # C(L)
        error_right = self._mean_squared_error(right_y) # C(R)
        error_set = self._mean_squared_error(y) # C(S)
        
        return error_set - (len(left_y) / m * error_left + len(right_y) / m * error_right)
        # G(j, theta) : C(S) - (|L| / |S| * C(L) + |R| / |S| * C(R))
    
    def _split_function(self, X, y):
        m, n = X.shape
        best_split = None
        best_gain = float("-inf")

        feature_indices = None
        if self.max_features is None:
            feature_indices = np.arange(n)
        elif isinstance(self.max_features, int):
            feature_indices = np.random.choice(n, self.max_features, replace=False)
        elif self.max_features == "sqrt":
            feature_indices = np.random.choice(n, int(np.sqrt(n)), replace=False)
        elif self.max_features == "log2":
            feature_indices = np.random.choice(n, int(np.log2(n)), replace=False)

        for feature_index in feature_indices:
            if self.verbosity > 0:
                print(f"Decision Tree; feature_index : {feature_index}/{feature_indices}")
            thresholds = np.unique(X[:, feature_index])  # valeurs uniques de cette feature
            for threshold in thresholds:  # chaque seuil unique
                if self.verbosity > 0:
                    print(f"Decision Tree; {feature_index}; threshold : {threshold}")

                left_mask = X[:, feature_index] < threshold  # sous-ensemble L
                right_mask = ~left_mask  # sous-ensemble R
                left_y, right_y = y[left_mask], y[right_mask]  # targets correspondantes

                # Si un des sous-ensembles contient moins de données que le min_samples_leaf, on l'ignore
                if len(left_y) < self.min_samples_leaf or len(right_y) < self.min_samples_leaf:
                    continue

                # Si le nombre d'échantillons dans un sous-ensemble est inférieur au min_samples_split, on l'ignore
                if len(left_y) < self.min_samples_split or len(right_y) < self.min_samples_split:
                    continue

                # Calcul du gain (à maximiser)
                gain = self._gain(y, left_y, right_y)

                if gain > best_gain:  # Si ce split est meilleur
                    if self.verbosity > 0:
                        print(f"Decision Tree; {feature_index}; {threshold}; gain : {gain} > {best_gain}")
                    best_gain = gain
                    best_split = (feature_index, threshold)  # Meilleur index de feature et seuil

        return best_split

    
    def _build_tree(self, X, y, depth=0):
        def _mean(y):
            return TreeNode(value=1/X.shape[0] * np.sum(y)) # moyenne des prédictions
        
        # Si la profondeur maximale est atteinte
        if self.max_depth is not None and depth >= self.max_depth:
            return _mean(y)

        best_split = self._split_function(X, y)
        
        # Si aucun split n'a été trouvé, on retourne une feuille avec la classe majoritaire
        if best_split is None:
            return _mean(y)

        feature, threshold = best_split  # Meilleur split trouvé

        # Split binaire
        left_idx = X[:, feature] < threshold
        right_idx = ~left_idx

        # Vérification si les sous-ensembles gauche ou droit sont vides
        if len(y[left_idx]) == 0 or len(y[right_idx]) == 0:
            return _mean(y)

        if self.verbosity > 0:
            print(f"Decision Tree; build_tree; depth : {depth}/{self.max_depth}")
        # Construction des sous-arbres
        left_tree = self._build_tree(X[left_idx], y[left_idx], depth + 1)
        right_tree = self._build_tree(X[right_idx], y[right_idx], depth + 1)

        return TreeNode(feature_index=feature, threshold=threshold, left=left_tree, right=right_tree)
    
    def _predict_sample(self, x, tree):
        if self.verbosity > 0:
            print(f"Decision Tree; predict_sample : {x}, {tree}")
        if tree.value is not None:  # Si c'est une feuille
            return tree.value
        if x[tree.feature_index] < tree.threshold:  # Si l'échantillon va à gauche
            return self._predict_sample(x, tree.left)
        else:  # Sinon, il va à droite
            return self._predict_sample(x, tree.right)

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self.tree = self._build_tree(X, y)  # Construction de l'arbre
        return self

    def predict(self, X):
        X = np.array(X)
        return np.array([self._predict_sample(x, self.tree) for x in X])

class RandomForestRegressor:
    def __init__(self, n_estimators=100, max_features="sqrt", max_depth=5, min_samples_leaf=10, min_samples_split=5, verbosity=0):
        self.n_estimators = n_estimators
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.verbosity = verbosity
        self.model_list = []

    def _bootstrap_samples(self, X, y):
        random_index = np.random.choice(len(X), size=len(X), replace=True)
        return X[random_index], y[random_index]

    def _train_estimator(self, X, y):
        for i in range(self.n_estimators):
            if self.verbosity > -1:
                print(f"Random Forest; train_estimator; iteration : {i}")
            X_boostrap, y_bootstrap = self._bootstrap_samples(X, y)
            model = DecisionTreeRegressor(self.max_features, self.max_depth, self.min_samples_leaf, self.min_samples_split)
            model.fit(X_boostrap, y_bootstrap)
            self.model_list.append(model)

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self._train_estimator(X, y)

    def predict(self, X):
        X = np.array(X)
        predictions_list = np.array([model.predict(X) for model in self.model_list])
        return predictions_list.mean(axis=0) # moyenne des prédictions pour chaque échantillons de X

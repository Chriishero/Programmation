import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split

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
    
class GradientBoostingClassifier:
    def __init__(self, n_estimators=200, learning_rate=0.1, max_features='sqrt', max_depth=3, min_samples_leaf=10, min_samples_split=5, loss='log-loss', subsample=0.9, early_stopping_rounds=20, validation_fraction=0.1):
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

        self.model_list = []
        self.n_classes = 0

    def _softmax(self, logits):
        exp = np.exp(logits - np.max(logits, axis=1, keepdims=True))
        return exp / np.sum(exp, axis=1, keepdims=True)
    
    def _gradient(self, y_onehot, proba):
        if self.loss == 'log-loss':
            return proba - y_onehot
    
    def _subsample(self, X, gradient):
        m, n = X.shape
        random_index = np.random.choice(m, int(m * self.subsample), replace=True)
        return X[random_index], gradient[random_index]
    
    def _gradient_descent(self, X, y):
        if self.early_stopping_rounds or self.validation_fraction:
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
                    X_sub, gradient_sub = X_train, gradient[:, k]

                model = DecisionTreeRegressor(self.max_features, self.max_depth, self.min_samples_leaf, self.min_samples_split)
                model.fit(X_sub, -gradient_sub)
                self.model_list[k].append(model)
                logits[:, k] = logits[:, k] + self.learning_rate * model.predict(X_train)
                
            if X_val is not None:
                for k in range(self.n_classes):
                    val_logits[:, k] = val_logits[:, k] + self.learning_rate * self.model_list[k][-1].predict(X_val)

                val_pred = np.argmax(self._softmax(val_logits), axis=1)
                score = accuracy_score(y_val, val_pred)
                if score > best_score:
                    best_score = score
                    best_iter = i
                elif i - best_iter >= self.early_stopping_rounds:
                    print(f"stop at {i}")
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
                logits[:, k] = logits[:, k] + self.learning_rate * model.predict(X)

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
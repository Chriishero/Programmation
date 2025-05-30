import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.metrics import accuracy_score

# Générer un dataset avec plusieurs classes
X, y = make_classification(n_features=10, n_samples=500, n_informative=2, n_clusters_per_class=1, n_classes=4, random_state=0)

class TreeNode:
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, value=None):
        self.feature_index = feature_index  # j
        self.threshold = threshold          # theta
        self.left = left                    # sous-arbre gauche (xj < theta)
        self.right = right                  # sous-arbre droit (xj >= theta)
        self.value = value                  # prédiction w_j si feuille

class DecisionTreeClassifier:
    def __init__(self, max_depth=None, min_samples_split=2, min_samples_leaf=1):
        self.max_depth = max_depth
        self.min_samples_split = min_samples_split
        self.min_samples_leaf = min_samples_leaf
        self.tree = None # racine de l'arbre

    def _entropy(self, y):
        m = len(y)
        _, counts = np.unique(y, return_counts=True)  # Comptage des occurrences pour chaque classe
        probabilities = 1/m * counts  # Probabilités de chaque classe
        return -np.sum(probabilities * np.log2(probabilities + 1e-15))  # Entropie
    
    def _gain_function(self, y, left_y, right_y):
        m = len(y)
        entropy_left = self._entropy(left_y) # C(L)
        entropy_right = self._entropy(right_y) # C(R)
        entropy_set = self._entropy(y) # C(S)
        
        return entropy_set - (len(left_y) / m * entropy_left + len(right_y) / m * entropy_right)
        # G(j, theta) : C(S) - (|L| / |S| * C(L) + |R| / |S| * C(R))

    def _best_split(self, X, y):
        best_gain = float("-inf")
        best_split = None
        m, n = X.shape

        for feature_index in range(n):
            thresholds = np.unique(X[:, feature_index])  # valeurs uniques de cette feature
            for threshold in thresholds:  # chaque seuil unique
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
                gain = self._gain_function(y, left_y, right_y)

                if gain > best_gain:  # Si ce split est meilleur
                    best_gain = gain
                    best_split = (feature_index, threshold)  # Meilleur index de feature et seuil

        return best_split

    def _build_tree(self, X, y, depth=0):
        # Si tous les exemples ont la même classe
        if len(set(y)) == 1:
            return TreeNode(value=y[0])

        # Si la profondeur maximale est atteinte
        if self.max_depth is not None and depth >= self.max_depth:
            majority_class = np.bincount(y).argmax()  # Classe majoritaire
            return TreeNode(value=majority_class)

        best_split = self._best_split(X, y)
        
        # Si aucun split n'a été trouvé, on retourne une feuille avec la classe majoritaire
        if best_split is None:
            majority_class = np.bincount(y).argmax()  # Classe majoritaire
            return TreeNode(value=majority_class)

        feature, threshold = best_split  # Meilleur split trouvé

        # Split binaire
        left_idx = X[:, feature] < threshold
        right_idx = ~left_idx

        # Vérification si les sous-ensembles gauche ou droit sont vides
        if len(y[left_idx]) == 0 or len(y[right_idx]) == 0:
            majority_class = np.bincount(y).argmax()  # Classe majoritaire
            return TreeNode(value=majority_class)

        # Construction des sous-arbres
        left_tree = self._build_tree(X[left_idx], y[left_idx], depth + 1)
        right_tree = self._build_tree(X[right_idx], y[right_idx], depth + 1)

        return TreeNode(feature_index=feature, threshold=threshold, left=left_tree, right=right_tree)

    def _predict_sample(self, x, tree):
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

model = DecisionTreeClassifier(max_depth=5, min_samples_split=5, min_samples_leaf=10)
model.fit(X, y)

y_pred = model.predict(X)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, c="r")
plt.title(f"Accuracy : {accuracy_score(y, y_pred)}")
plt.legend()
plt.show()
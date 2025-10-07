import numpy as np
from sklearn.datasets import make_classification
from sklearn.metrics import accuracy_score

class TreeNode:
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, value=None):
        self.feature_index = feature_index  # j
        self.threshold = threshold          # theta
        self.left = left                    # sous-arbre gauche (xj < theta)
        self.right = right                  # sous-arbre droit (xj >= theta)
        self.value = value                  # prédiction w_j si feuille

class DecisionTreeClassifier:
    def __init__(self, max_depth=None, min_samples_split=2, min_samples_leaf=1, max_features=None, splitter="best", random_state=None):
        self.max_depth = max_depth
        self.min_samples_split = min_samples_split
        self.min_samples_leaf = min_samples_leaf
        self.max_features = max_features
        self.splitter = splitter
        self.random_state = random_state

        self.tree_ = None # racine de l'arbre
        self.rng = np.random.RandomState(random_state)

    def _entropy(self, y):
        m = len(y)
        _, counts = np.unique(y, return_counts=True)  # Comptage des occurrences pour chaque classe
        probabilities = 1/m * counts  # Probabilités de chaque classe
        return -np.sum(probabilities * np.log2(probabilities + 1e-15))  # Entropie
    
    def _gain_function(self, y, left_y, right_y):
        m_S, m_L, m_R = len(y), len(left_y), len(right_y)
        C_S = self._entropy(y) # C(S)
        C_L = self._entropy(left_y) # C(L)
        C_R = self._entropy(right_y) # C(R)
        
        return C_S - (m_L / m_S * C_L + m_R / m_S * C_R)
        # G(j, theta) : C(S) - (|L| / |S| * C(L) + |R| / |S| * C(R))

    def _select_features(self, n):
        k = None 
        if isinstance(self.max_features, int) or isinstance(self.max_features, float):
            raise ValueError(f"max_features ({self.max_features}) is greater than the number of features ({n})")
        elif self.max_features == "sqrt":
            k = max(1, int(np.sqrt(n)))
        elif self.max_features == "log2":
            k = max(1, int(np.log2(n)))
        else:
            return np.arange(n) # initialement, toutes les features sont disponibles
        
        return self.rng.choice(n, k, replace=False)

    def _choose_split(self, X, y, feature_index, threshold, best_gain):
        is_split = False

        left_mask = X[:, feature_index] < threshold  # sous-ensemble L
        right_mask = ~left_mask  # sous-ensemble R

        # Si un des sous-ensembles contient moins de données que le min_samples_leaf, on l'ignore
        if len(y[left_mask]) < self.min_samples_leaf or len(y[right_mask]) < self.min_samples_leaf:
            return False, 0

        # Calcul du gain (à maximiser)
        gain = self._gain_function(y, y[left_mask], y[right_mask])
        if gain < 0: # un gain négatif augmente l'entropie : mauvais
            return False, 0
        elif gain > best_gain:  # Si ce split est meilleur
            best_gain = gain
            is_split = True
        elif gain == best_gain: # Si ils sont égaux
            if self.rng.rand() < 0.5: # Choix aléatoire pour éviter le biais de prendre l'actuel
                is_split = True
        
        return is_split, best_gain

    def _best_split(self, X, y):
        m, n = X.shape

        best_gain = float("-inf")
        best_split = None
        indices = self._select_features(n)

        if self.splitter == "best":
            for feature_index in indices:
                thresholds = np.unique(X[:, feature_index])  # valeurs uniques de cette feature
                self.rng.shuffle(thresholds) # évite le biais d'avoir toujours des seuils dans le même ordre
                for threshold in thresholds:  # chaque seuil unique
                    is_split, gain = self._choose_split(X, y, feature_index, threshold, best_gain)
                    if is_split is not False:
                        best_split = (feature_index, threshold)
                        best_gain = gain
        elif self.splitter == "random":
            for _ in range(max(1, n)):
                feature_index = self.rng.choice(indices)
                thresholds = np.unique(X[:, feature_index])
                threshold = self.rng.choice(thresholds)
                is_split, gain = self._choose_split(X, y, feature_index, threshold, best_gain)
                if is_split is not False:
                    best_split = (feature_index, threshold)
                    best_gain = gain

        return best_split

    def _build_tree(self, X, y, depth=0):
        def _leaf_value():
            return TreeNode(value=np.bincount(y).argmax()) # Classe majoritaire

        # Si la profondeur maximale est atteinte
        if self.max_depth is not None and depth >= self.max_depth:
            return _leaf_value()

        best_split = self._best_split(X, y)
        
        # Si aucun split n'a été trouvé, on retourne une feuille avec la classe majoritaire
        if best_split is None:
            return _leaf_value()

        feature, threshold = best_split  # Meilleur split trouvé

        # Split binaire
        left_mask = X[:, feature] < threshold
        right_mask = ~left_mask

        # Si le nombre d'échantillons du noeud est inférieur au min_samples_split, il devient une feuille
        if len(y) < self.min_samples_split:
            return _leaf_value()

        # Vérification si les sous-ensembles gauche ou droit sont vides
        if len(y[left_mask]) == 0 or len(y[right_mask]) == 0:
            return _leaf_value()

        # Construction des sous-arbres
        left_tree = self._build_tree(X[left_mask], y[left_mask], depth + 1)
        right_tree = self._build_tree(X[right_mask], y[right_mask], depth + 1)

        return TreeNode(feature_index=feature, threshold=threshold, left=left_tree, right=right_tree)

    def _predict_sample(self, x, tree):
        if tree.value is not None:  # Si c'est une feuille
            return tree.value
        if x[tree.feature_index] < tree.threshold:  # Si l'échantillon va à gauche
            return self._predict_sample(x, tree.left)
        else:  # Sinon, il va à droite
            return self._predict_sample(x, tree.right)

    def fit(self, X, y, sample_weight=None):
        X = np.array(X)
        y = np.array(y)

        self.tree_ = self._build_tree(X, y)  # Construction de l'arbre

    def predict(self, X):
        X = np.array(X)
        return np.array([self._predict_sample(x, self.tree_) for x in X])
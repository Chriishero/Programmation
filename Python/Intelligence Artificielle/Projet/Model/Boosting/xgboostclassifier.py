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
    def __init__(self, max_features='sqrt', max_depth=None, min_samples_split=None, min_samples_leaf=None, reg_lambda=1.0, reg_gamma=0.0,):
        self.max_depth = max_depth
        self.max_features = max_features
        self.min_samples_split = min_samples_split
        self.min_samples_leaf = min_samples_leaf
        self.reg_lambda = reg_lambda
        self.reg_gamma = reg_gamma

        self.tree = None # racine de l'arbre
    
    def _gain_function(self, G_left, G_right, H_left, H_right):
        return 1/2 * (G_left**2 / (H_left + self.reg_lambda) + G_right**2 / (H_right + self.reg_lambda)
                      - (G_left + G_right)**2 / (H_left + H_right + self.reg_lambda)) - self.reg_gamma

    def _best_split(self, X, gradients, hessians):
        m, n = X.shape
        best_gain = float("-inf")
        best_split = None
        feature_indices = np.arange(n)

        if isinstance(self.max_features, int):
           feature_indices = np.random.choice(n, self.max_features, replace=False)
        elif self.max_features == 'sqrt':
            feature_indices = np.random.choice(n, int(np.sqrt(n)), replace=False)
        elif self.max_features == 'log2':
            feature_indices = np.random.choice(n, int(np.log2(n)), replace=False)

        for feature_index in feature_indices:
            thresholds = np.unique(X[:, feature_index])  # valeurs uniques de cette feature
            for threshold in thresholds:  # chaque seuil unique
                left_mask = X[:, feature_index] < threshold  # sous-ensemble L
                right_mask = ~left_mask  # sous-ensemble R
                left_gradients, right_gradients = gradients[left_mask], gradients[right_mask]  # targets correspondantes

                # Si un des sous-ensembles contient moins de données que le min_samples_leaf, on l'ignore
                if len(left_gradients) < self.min_samples_leaf or len(right_gradients) < self.min_samples_leaf:
                    continue

                # Si le nombre d'échantillons dans un sous-ensemble est inférieur au min_samples_split, on l'ignore
                if len(left_gradients) < self.min_samples_split or len(right_gradients) < self.min_samples_split:
                    continue

                # Calcul du gain (à maximiser)
                G_left = np.sum(left_gradients)
                G_right = np.sum(right_gradients)
                H_left = np.sum(hessians[left_mask])
                H_right = np.sum(hessians[right_mask])
                gain = self._gain_function(G_left, G_right, H_left, H_right)

                if gain > best_gain:  # Si ce split est meilleur
                    best_gain = gain
                    best_split = (feature_index, threshold)  # Meilleur index de feature et seuil

        return best_split

    def _build_tree(self, X, gradients, hessians, depth=0):
        def _leaf_values():
            G = np.sum(gradients)
            H = np.sum(hessians)
            return TreeNode(value=-G / (H + self.reg_lambda))

        # Si la profondeur maximale est atteinte
        if self.max_depth is not None and depth >= self.max_depth:
            return _leaf_values()

        best_split = self._best_split(X, gradients, hessians)
        
        # Si aucun split n'a été trouvé, on retourne une feuille avec la classe majoritaire
        if best_split is None:
            return _leaf_values()

        feature, threshold = best_split  # Meilleur split trouvé

        # Split binaire
        left_idx = X[:, feature] < threshold
        right_idx = ~left_idx

        # Vérification si les sous-ensembles gauche ou droit sont vides
        if len(gradients[left_idx]) == 0 or len(gradients[right_idx]) == 0:
            return _leaf_values()

        # Construction des sous-arbres
        left_tree = self._build_tree(X[left_idx], gradients[left_idx], hessians[left_idx], depth + 1)
        right_tree = self._build_tree(X[right_idx], gradients[right_idx], hessians[right_idx], depth + 1)

        return TreeNode(feature_index=feature, threshold=threshold, left=left_tree, right=right_tree)

    def _predict_sample(self, x, tree):
        if tree.value is not None:  # Si c'est une feuille
            return tree.value
        if x[tree.feature_index] < tree.threshold:  # Si l'échantillon va à gauche
            return self._predict_sample(x, tree.left)
        else:  # Sinon, il va à droite
            return self._predict_sample(x, tree.right)

    def fit(self, X, gradients, hessians):
        X = np.array(X)
        gradients = np.array(gradients)
        hessians = np.array(hessians)

        self.tree = self._build_tree(X, gradients, hessians)  # Construction de l'arbre

    def predict(self, X):
        X = np.array(X)
        return np.array([self._predict_sample(x, self.tree) for x in X])

class XGBoostClassifier:
    def __init__(self, n_estimators=100, learning_rate=0.2, max_features='sqrt', max_depth=3, min_samples_leaf=1, min_samples_split=2, reg_lambda=1.0, reg_gamma=0.0, loss='log_loss', subsample=1.0, early_stopping_rounds=20, validation_fraction=0.1):
        self.n_estimators = n_estimators
        self.learning_rate = learning_rate
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.reg_lambda = reg_lambda
        self.reg_gamma = reg_gamma
        self.loss = loss
        self.subsample = subsample
        self.early_stopping_rounds = early_stopping_rounds
        self.validation_fraction = validation_fraction
        
        self.model_list = []
        self.n_classes = 0

    def _softmax(self, logits): # probatilité par classe par exemple
        exp_logits = np.exp(logits - np.max(logits, axis=1, keepdims=True))
        return exp_logits / np.sum(exp_logits, axis=1, keepdims=True)

    def _gradient_hessian(self, y_onehot, proba):
        if self.loss == "log_loss":
            # Gradient = p_k - y_k
            gradient = proba - y_onehot
            hessian = proba * (1 - proba)
            return gradient, hessian

    def _subsample(self, X, gradient, hessian):
        m = X.shape[0]
        indices = np.random.choice(m, int(m * self.subsample), replace=False)
        return X[indices], gradient[indices], hessian[indices]

    def _gradient_descent(self, X, y):
        if self.validation_fraction and self.early_stopping_rounds: # s'il y a early_stopping_rounds
            X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=self.validation_fraction, random_state=0)
        else:
            X_train, y_train = X, y
            X_val = y_val = None

        m, n = X_train.shape
        self.n_classes = np.max(y_train) + 1 # nombre de classes du datasets

        logits = np.zeros((m, self.n_classes))  # Initial logits (f0 = 0) (logit = prédictions d'UNE classe)
        y_onehot = np.eye(self.n_classes)[y_train]

        if X_val is not None: # s'il y a early_stopping_rounds
            val_logits = np.zeros((X_val.shape[0], self.n_classes))
            best_val_score = float("-inf")
            best_iteration = 0

        self.model_list = [[] for _ in range(self.n_classes)] # crée une liste de liste, une pour chaque classe

        for i in range(self.n_estimators):
            proba = self._softmax(logits) # transforme les logits en probabilités
            gradient, hessian = self._gradient_hessian(y_onehot, proba) 

            for k in range(self.n_classes): # pour chaque classe
                if self.subsample < 1.0:
                    X_sub, grad_sub, hess_sub = self._subsample(X_train, gradient[:, k], hessian[:, k])
                else:
                    X_sub, grad_sub, hess_sub = X_train, gradient[:, k], hessian[:, k]

                tree = DecisionTreeRegressor(max_features=self.max_features, max_depth=self.max_depth, 
                                             min_samples_leaf=self.min_samples_leaf, min_samples_split=self.min_samples_split,
                                             reg_lambda=self.reg_lambda, reg_gamma=self.reg_gamma)
                tree.fit(X_sub, grad_sub, hess_sub)  # Descente de gradient : on apprend sur -∇L
                self.model_list[k].append(tree)

                logits[:, k] += self.learning_rate * tree.predict(X_train) # fi := fi-1 + alpha * Fi

            if X_val is not None: # s'il y a early_stopping_rounds
                for k in range(self.n_classes): # pour chaque classe
                    val_logits[:, k] += self.learning_rate * self.model_list[k][-1].predict(X_val) # fi := fi-1 + alpha * Fi
                    # self.model_list[k][-1] : dernier modèle de la classe k
                    # val_logits[:, k] : logits de la classe k

                val_pred = np.argmax(self._softmax(val_logits), axis=1) # classe qui maximise le softmax
                score = accuracy_score(y_val, val_pred)

                if score > best_val_score:
                    best_val_score = score
                    best_iteration = i
                elif i - best_iteration >= self.early_stopping_rounds:
                    print(f"Early stopping at iteration {i}")
                    break

    def fit(self, X, y):
        self._gradient_descent(np.array(X), np.array(y))

    def predict(self, X):
        X = np.array(X)
        logits = np.zeros((X.shape[0], self.n_classes))
        for k in range(self.n_classes):
            for tree in self.model_list[k]:
                logits[:, k] += self.learning_rate * tree.predict(X) # logits de la classe k
        return np.argmax(self._softmax(logits), axis=1) # classe qui maximise le softmax

# Test
X, y = make_classification(n_samples=500, n_features=10, n_informative=2, n_clusters_per_class=1, n_classes=4, random_state=0)
model = XGBoostClassifier()
model.fit(X, y)
y_pred = model.predict(X)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, color='r')
plt.title(f'Accuracy: {accuracy_score(y, y_pred):.3f}')
plt.legend()
plt.show()

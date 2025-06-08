import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_friedman1, make_regression
from sklearn.metrics import r2_score
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
    
class XGBoostRegressor:
    def __init__(self, n_estimators=100, learning_rate=0.2, max_features="sqrt", max_depth=3, min_samples_leaf=10, min_samples_split=5,
                 reg_lambda=1.0, reg_gamma=0.0, subsample=0.9, loss='mean_squared', early_stopping_rounds=20, validation_fraction=0.1):
        self.n_estimators = n_estimators
        self.learning_rate = learning_rate
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split
        self.reg_lambda = reg_lambda
        self.reg_gamma = reg_gamma
        self.subsample = subsample # réduis la variance (bootstrap)
        self.loss = loss
        self.early_stopping_rounds = early_stopping_rounds
        self.validation_fraction = validation_fraction

        self.initial_prediction = None # F0
        self.model_list = []

    def _compute_gradient_hessian(self, y, y_pred):
        if self.loss == 'mean_squared':
            gradient = y_pred - y
            hessian = np.ones_like(y)
            return gradient, hessian

    def _subsample_function(self, X, gradient, hessian):
        m, n = X.shape
        random_index = np.random.choice(m, int(m * self.subsample), replace=False)
        return X[random_index], gradient[random_index], hessian[random_index]

    def _gradient_descent(self, X, y):
        if self.early_stopping_rounds and self.validation_fraction: # s'il y a early_stopping_rounds
            X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=self.validation_fraction, random_state=0)
        else:
            X_train, y_train = X, y
            X_val = y_val = None

        m, n = X_train.shape
        self.initial_prediction = 1/m * np.sum(y_train) # moyenne des valeurs réels (y)
        y_pred = np.full(m, self.initial_prediction) # prédictions initiales pour les exemples

        if X_val is not None: # s'il y a early_stopping_rounds
            pred_val = np.full(X_val.shape[0], self.initial_prediction) # prédiction initiales sur le test de validation
            best_score = float("-inf")
            best_iter = None

        for i in range(self.n_estimators):
            gradient, hessian = self._compute_gradient_hessian(y_pred, y_train)

            X_sub, grad_sub, hess_sub = self._subsample_function(X_train, gradient, hessian) # bootstrap
            model = DecisionTreeRegressor(self.max_features, self.max_depth, self.min_samples_leaf, self.min_samples_split,
                                            self.reg_lambda, self.reg_gamma)
            model.fit(X_sub, -grad_sub, hess_sub)
            self.model_list.append(model)
            y_pred += self.learning_rate * model.predict(X_train) # fi := fi-1 + alpha * Fi
            
            if X_val is not None: # s'il y a early_stopping_rounds
                pred_val += self.learning_rate * model.predict(X_val) # fi := fi-1 + alpha * Fi
                score = r2_score(y_val, pred_val)
                if score > best_score:
                    best_score = score
                    best_iter = i
                elif i - best_iter >= self.early_stopping_rounds:
                    print(f'break at {i}')
                    break

    def fit(self, X, y):
        self._gradient_descent(np.array(X), np.array(y))

    def predict(self, X):
        X = np.array(X)
        y_pred = np.full(X.shape[0], self.initial_prediction)
        for model in self.model_list:
            y_pred += self.learning_rate * model.predict(X) # fi := fi-1 + alpha * Fi
        return y_pred

X, y = make_friedman1(n_samples=1000, n_features=10, noise=1, random_state=0)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, random_state=0)

model = XGBoostRegressor()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

plt.figure()
plt.scatter(y_test, y_pred)
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], color='r')
plt.title(f'{r2_score(y_test, y_pred)}')
plt.show()
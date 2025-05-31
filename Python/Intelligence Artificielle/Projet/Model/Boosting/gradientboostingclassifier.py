import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.metrics import accuracy_score
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import train_test_split

class GradientBoostingClassifier:
    def __init__(self, n_iterations=100, learning_rate=0.2, max_depth=3, loss='log_loss', subsample=0.9, early_stopping_rounds=20, validation_fraction=0.1):
        self.n_iterations = n_iterations
        self.learning_rate = learning_rate
        self.max_depth = max_depth
        self.loss = loss
        self.subsample = subsample
        self.early_stopping_rounds = early_stopping_rounds
        self.validation_fraction = validation_fraction
        
        self.model_list = []
        self.n_classes = 0

    def _softmax(self, logits): # probatilité par classe par exemple
        exp_logits = np.exp(logits - np.max(logits, axis=1, keepdims=True))
        return exp_logits / np.sum(exp_logits, axis=1, keepdims=True)

    def _gradient(self, y_onehot, proba):
        if self.loss == "log_loss":
            # Gradient = p_k - y_k
            return proba - y_onehot

    def _subsample(self, X, gradient):
        m = X.shape[0]
        indices = np.random.choice(m, int(m * self.subsample), replace=True)
        return X[indices], gradient[indices]

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

        for i in range(self.n_iterations):
            proba = self._softmax(logits) # transforme les logits en probabilités
            gradient = self._gradient(y_onehot, proba) 

            for k in range(self.n_classes): # pour chaque classe
                if self.subsample < 1.0:
                    X_sub, grad_sub = self._subsample(X_train, gradient[:, k])
                else:
                    X_sub, grad_sub = X_train, gradient[:, k]

                tree = DecisionTreeRegressor(max_depth=self.max_depth)
                tree.fit(X_sub, -grad_sub)  # Descente de gradient : on apprend sur -∇L
                self.model_list[k].append(tree)

                logits[:, k] += self.learning_rate * tree.predict(X_train) # fi := fi-1 + alpha * Fi

            if X_val is not None: # s'il y a early_stopping_rounds
                for k in range(self.n_classes): # pour chaque classe
                    val_logits[:, k] += self.learning_rate * self.model_list[k][-1].predict(X_val) # fi := fi-1 + alpha * Fi
                    # self.model_list[k][-1] : dernier arbre de la classe k
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
model = GradientBoostingClassifier()
model.fit(X, y)
y_pred = model.predict(X)

plt.figure()
plt.scatter(X[:, 0], y)
plt.plot(X[:, 0], y_pred, color='r')
plt.title(f'Accuracy: {accuracy_score(y, y_pred):.3f}')
plt.legend()
plt.show()

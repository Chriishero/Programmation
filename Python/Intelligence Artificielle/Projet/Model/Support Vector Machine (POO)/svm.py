import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.metrics import accuracy_score

X, y = make_classification(n_samples=500, n_features=10, n_informative=2, n_classes=2, random_state=0)
y = y * 2 - 1  # Convertir les classes en +1 et -1

class SVM:
    def __init__(self, n_iteration=25, regularization=1, kernel="RBF", gamma=0.5, polynomial_constant=1, polynom_degree=2):
        self.n_iteration = n_iteration
        self.C = regularization
        self.kernel = kernel
        self.gamma = gamma
        self.polynomial_constant = polynomial_constant
        self.polynom_degree = polynom_degree
        self.X_train = None
        self.y_train = None
        self.K = None
        self.alpha = None
        self.b = None
        self.cost_history = np.zeros(n_iteration)

    def kernels_function(self, X, Z):
        if self.kernel == "linear":
            return X @ Z.T
        if self.kernel == "polynomial":
            return (X @ Z.T + self.polynomial_constant) ** self.polynom_degree
        if self.kernel == "RBF":
            return np.exp(-self.gamma * np.linalg.norm(X[:, np.newaxis, :] - Z, axis=2) ** 2)

    def dual_objective_function(self, y):
        return np.sum(self.alpha) - 1 / 2 * self.alpha @ ((np.outer(y, y) * self.K) @ self.alpha) 
        # np.outer(y, y) : produit élément par élément : donne une matrice

    def sequential_minimal_optimization(self, X, y):
        m, n = X.shape
        self.alpha = np.zeros(m)
        self.b = 0
        
        for iteration in range(self.n_iteration):
            for i in range(m):
                # Choix de j, un autre point à optimiser
                j = np.random.choice([k for k in range(m) if k != i])
                
                # Sauvegarde des anciennes valeurs de alpha
                alpha_old_i = self.alpha[i]
                alpha_old_j = self.alpha[j]
                
                # Mise à jour de alpha[j]
                zeta = alpha_old_i * y[i] + alpha_old_j * y[j]
                self.alpha[j] = (1 - y[i] * self.K[i, j] * zeta) / (self.K[j, j] - self.K[i, j])
                
                # Clipper alpha[j] pour être dans la plage [0, C]
                self.alpha[j] = np.clip(self.alpha[j], 0, self.C)
                
                # Mise à jour de alpha[i]
                self.alpha[i] = self.alpha[i] + y[i] * y[j] * (alpha_old_j - self.alpha[j])
                
                # Clipper alpha[i] pour être dans la plage [0, C]
                self.alpha[i] = np.clip(self.alpha[i], 0, self.C)
                
                # Mise à jour du biais b
                E_i = np.sum(self.alpha * y.ravel() * self.K[i, :]) + self.b - y[i]
                E_j = np.sum(self.alpha * y.ravel() * self.K[j, :]) + self.b - y[j]
                b1 = self.b - E_i - y[i] * (self.alpha[i] - alpha_old_i) * self.K[i, i] - y[j] * (self.alpha[j] - alpha_old_j) * self.K[i, j]
                b2 = self.b - E_j - y[i] * (self.alpha[i] - alpha_old_i) * self.K[i, j] - y[j] * (self.alpha[j] - alpha_old_j) * self.K[j, j]
                
                # Calcul final du biais b
                self.b = (b1 + b2) / 2
            
            # Calcul de la fonction objectif (pour suivre la progression)
            self.cost_history[iteration] = self.dual_objective_function(y)

    def fit(self, X, y):
        X = np.array(X)
        y = np.array(y)

        self.X_train = X
        self.y_train = y

        self.K = self.kernels_function(X, X)
        self.sequential_minimal_optimization(X, y)

    def predict(self, X):
        X = np.array(X)
        K = self.kernels_function(X, self.X_train)
        return np.sign(np.sum(self.alpha * self.y_train * K, axis=1) + self.b)  # Calcul des prédictions avec le noyau

# Entraîner le modèle
model = SVM(kernel="RBF", polynom_degree=2, n_iteration=25)  # Augmenter le nombre d'itérations
model.fit(X, y)

# Prédictions
y_pred = model.predict(X)

# Visualisation de l'évolution de la fonction objectif
plt.figure()
plt.plot(range(model.n_iteration), model.cost_history)
plt.title("Evolution de la fonction objectif")

# Visualisation des résultats
plt.figure()
plt.scatter(X[:, 0], y, label="Données réelles")
plt.plot(X[:, 0], y_pred, c="r", label="Prédictions")
plt.title(f"Accuracy : {accuracy_score(y, y_pred)}")
plt.legend()
plt.show()

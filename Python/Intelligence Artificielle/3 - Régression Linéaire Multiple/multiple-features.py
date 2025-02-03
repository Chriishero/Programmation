import numpy as np
from sklearn.datasets import make_regression # permet de générer aléatoirement des données
import matplotlib.pyplot as plt # permet de visualiser des graph

x, y = make_regression(n_samples = 100, n_features=2, noise = 10) # génére des données dans 2 tableaux : x et y, de 100 échantillons (lignes), 2 variables (features) et un bruit de 20 (désordonnés)
print(f"Dimension du vecteur x : {x.shape}") # affiche les dimensions du vecteur matriciel 'x'
y = y.reshape(y.shape[0], 1) # redimensionne du vecteur 'y', avec le nombre de ligne dans 'y' (y.shape[0]) et 1 colonne
print(f"Dimension du vecteur x : {y.shape}")

# matrice X
X = np.hstack((x, np.ones((x.shape[0], 1)))) # 'htstack' cole le vecteur 'x' avec un vecteur remplie de 1 (np.ones()), même 'm' que 'x' et 1 colonne (n)
print(f"Dimension de la matrice X : {X.shape}")
print(X[:10])

theta = np.random.randn(3, 1) # créer un vecteur 'theta' de dimension 3x1, avec des paramètres aléatoires
print(theta)

# Modèle (linéaire)
def model(X, theta):
    return X.dot(theta) # retourne le produit matriciel de 'X' par 'theta'

# Fonction Coût
def cost_function(X, y, theta):
    m = len(y) # m = nombre d'exemple dans le dataset
    return 1/(2*m) * np.sum((model(X, theta) - y)**2)

# Gradients et Descente de Gradient
def grad(X, y, theta):
    m = len(y) # m = nombre d'exemple dans le dataset
    return 1/m * X.T.dot(model(X, theta) - y)

def gradient_descent(X, y, theta, learning_rate, n_iterations):
    cost_history = np.zeros(n_iterations)
    for i in range(0, n_iterations):
        theta = theta - learning_rate * grad(X, y, theta)
        cost_history[i] = cost_function(X, y, theta) # enregistre le coût du modèle pour chaque itération
    return theta, cost_history

# Coefficient de détermination
def coef_determination(y, pred):
    u = ((y - pred)**2).sum() # résidus, différence entre les valeurs et celles prédites par le modèle, de la somme des carrés
    v = ((y - y.mean())**2).sum() # somme total des carrés
    return 1 - u/v

n_iterations = 400
learning_rate = 0.1

theta_final, cost_history = gradient_descent(X, y, theta, learning_rate, n_iterations)
print(f"Theta Final : {theta_final}")

predictions = model(X, theta_final) # modèle final, grâce à la valeur de 'theta' (paramètre de la fonction) trouvé avec l'algorithm de la descente de gradient

print(f"Coefficient de détermination : {coef_determination(y, predictions)}")

plt.plot(x[:,0], predictions, c='r') # affiche la droite du modèle, par rapport à la features 'x1' du dataset 'x', en rouge
plt.scatter(x[:,0], y) # créer le graph y en fonction de la features 'x1' (x sur les abscisses)
#plt.plot(range(n_iterations), cost_history) # sur 1000 points, trâce le coût du modèle pour chaque point 'cost_history'
plt.show() # affiche le graph

plt.plot(x[:,1], predictions, c='r') # avec features 'x2'
plt.scatter(x[:,1], y) 
plt.show() 
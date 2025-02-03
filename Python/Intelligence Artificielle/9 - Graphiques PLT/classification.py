
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris

iris = load_iris() # charge le dataset des iris

x = iris.data # récupère les features (variables)
y = iris.target # récupère la target
name = list(iris.target_names)

print(f"x contient {x.shape[0]} exemples et {x.shape[1]} variables")
print(f"il y a {np.unique(y).size} classes")

plt.scatter(x[:, 0], x[:, 1], c=y, alpha=0.5, s=x[:,2]*100) # 'c=y' permet de colorier différement chaque classes d'iris
# 'alpha' : transparence
# 's' : taille des points, en fonction de la variable 3
plt.xlabel("longueur du sépal")
plt.ylabel("largeur du sépal")
plt.show()
"""
Le Pre-Processing c'est le fait de nettoyer, filtrer, normaliser des données avant de les données à l'algorithme de machine learning.
Encodage : convertie des données qualitatives (string) en valeur numérique.
    Encodage Ordinal : associe chaque catégorie d'une variable à un valeur décimale unique. Le problème est que la machine va pouvoir comparer les différentes catégorie.
    Encodage One Hot : représente chaque catégorie en un nombre binaire dans un tableau. Les algorithme ne peuvent plus comparer les différentes catégories.
        Chien : [0, 0, 1] | Chat : [0, 1, 0]
        
Sparse Matrix en format Coordinate (COO) : compresse une matrice de nombre binaire dans 3 tableau plus petit :
    [a, 0, 0, 0, 0]    values = [a,b,c]
    [0, 0, b, 0, 0]    row    = [0,1,3]
    [0, 0, 0, 0, 0]    cols   = [0,2,4]
    [0, 0, 0, 0, c]
    [0, 0, 0, 0, 0]

Normalisation : mets toutes les variables quantitatives à la même échelle (entre 0 et 1 par ex).
Imputation : remplace les données manquantes par certaines valeurs statistiques.
Sélection : sélectionne les variables les plus utilies au développement du modèle.
Extraction : génére de nouvelles variables à partir d'information caché dans le dataset.

Transformer : interface de programmation pour traiter l'ensemble des données, en transformant les données futures de la même manière qu'on était tranformé les données d'entrainement.
Pipeline : chaine de transformation, combination entre un transformer et un estimator

Transformer d'encodage : 
    LabelEncoder() : encode ordinalement la variable y (target) 
    OrdinalEncoder() : encode ordinalement les variables X (features)

    LabelBinarizer(sparse_output=bool) : encore en One Hot avec ou non une compression CSR la variable y (target)
    OneHotEncoder(sparse_output=True) : encore en One Hot avec une compression CSR (par défaut) les variables X (features)

Normalisation : 
    MinMaxScaler() : transforme chaque variable X de telle sorte à être comprise entre 0 et 1 : Xtrain_scaled = (Xtrain - Xtrain_min) / (Xtrain_max - Xtrain_min)    
                                                                                                Xtest_scaled = (Xtest - Xtrain_min) / (Xtrain_max - Xtrain_min)   
    StandardScaler : transforme de sorte à ce que chaque variable ait une moyenne de 0 et un écart type égale à 1 : Xscaled = (X - Xmoyenne) / Xécarttype
    Ces 2 méthodes de normalisation ne sont pas efficaces quand il y a des valeurs aberrantes (ouliers) dans un dataset.

    RobustScaler : transforme chaque variable X en étant peu sensible aux outliers : Xscaler = (X - mediane) / IQR
                                                                                    IQR : Interquartile : différence entre le 1er et 3ème quartile

Features Engineering : 
    PolynomialFeatures() : crée des variables polynomiales à partir des variables existantes. Pour un polynôme de degré 2 :
                           crée une colonne de biais (1), une colonne X, puis une colonne X², la machine va ensuite développer un modèle : ax² + bx + c
                                                                                    
transformer.fit(X_train) : développel a méthode de tranformation
transformer.transform(X_train) : utilise la transformation
transformer.inverse_transform(array) : inverse la transformation
"""

import numpy as np
from sklearn.preprocessing import LabelEncoder, OrdinalEncoder, LabelBinarizer, OneHotEncoder, MinMaxScaler, StandardScaler, RobustScaler, PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.datasets import load_iris
import matplotlib.pyplot as plt

y = np.array(["Chat", "Chien", "Chat", "Oiseau"])
X = np.array([["Chat", "Chien"], 
              ["Oui", "Chien"], 
              ["Oiseau", "Plumes"]])

encoder = LabelEncoder()
print(encoder.fit_transform(y))
print(encoder.inverse_transform(np.array([0,0,2,2,1])))

encoder = LabelBinarizer(sparse_output=True) # compresse en CSR
print(encoder.fit_transform(y))

encoder = OneHotEncoder() # compresse en CSR
print(encoder.fit_transform(X))

X = np.array([[70], [80], [120]])
scaler = StandardScaler()
print(scaler.fit_transform(X))

iris = load_iris()
X = iris.data
X_minmax = MinMaxScaler().fit_transform(X)
x_stdscl = StandardScaler().fit_transform(X)
x_robust = RobustScaler().fit_transform(X)

plt.figure(figsize=(10,6))
plt.scatter(X[:, 2], X[:, 3], label="original")
plt.scatter(X_minmax[:, 2], X_minmax[:, 3], label='MinMaxScaler', alpha=0.5)
plt.scatter(x_stdscl[:, 2], x_stdscl[:, 3], label='StandardScaler', alpha=0.5)
plt.scatter(x_robust[:, 2], x_robust[:, 3], label='RobustScaler', alpha=0.5)
plt.legend()
plt.show()

X = np.linspace(0,4,100).reshape((100, 1))
y = X**2 + 5*np.cos(X) + np.random.randn(100,1)

X_poly = PolynomialFeatures(3).fit_transform(X) # tranforme les variables x en variables polynomiales
model = LinearRegression().fit(X_poly, y)
y_pred = model.predict(X_poly)

plt.scatter(X, y)
plt.plot(X, y_pred, c='r', lw=3)
plt.show()

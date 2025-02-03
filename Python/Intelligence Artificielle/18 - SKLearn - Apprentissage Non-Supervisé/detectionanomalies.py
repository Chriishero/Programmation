"""
Apprentissage Non-Supervisé : la machine analyse la structure des données X pour apprendre elle-même à réaliser certains tâches.

Clustering : regroupe les données selon leurs ressemblances, classification non-supervisé
Détection d'anomalies : trouve les échantillons dont les caractéristiques (X) sont très éloignés de celles des autres échantillons.
    Isolation Forest : effectue un nombre de splits aléatoires, puis compte le nombre de splits qu'il faut pour isoler nos échantillons (faible = probabiltié d'anomalie)
        Hyper-Paramètres :
            contamination : pourcentage de données que l'on veut filtrer
        Méthodes : 
            fit(X) : entraine le modèle
            predict(X) : +1 : normale | -1 : anormale
    Local Outlier Factor : détecte les anomalies dans les données futures 

Réduction de la dimension : en étudiant la structure de nos données, la machine apprend à la simplifier tout en conservant les principales informations.
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.ensemble import IsolationForest
from sklearn.datasets import load_digits

digits = load_digits()
images = digits.images
X = digits.data
y = digits.target

model = IsolationForest(random_state=0, contamination=0.02)
model.fit(X)
outliers = model.predict(X) == -1 # mets dans la variable 'outliers', toutes les prédictions égales à -1
plt.imshow(images[outliers][0]) # affiche la première anomalie du dataset
plt.title(y[outliers][0])
plt.show()
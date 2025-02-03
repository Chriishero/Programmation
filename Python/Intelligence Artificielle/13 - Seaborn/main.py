"""
sns.pairplot(dataset, hue='column') : trace des graphiques pour chaques relations entre toutes le variables, et colors
en fonction des valeurs de la colonne 'column'

Structures de la majorité des fonctions Seaborn :
sns.fonction(x, y, data, hue, size, style)
x, y, data : donnée à afficher
hue, size, style : segmentation

Visualiser des catégories :
sns.catplot()
sns.boxplot()

Visualiser des distributions : 
sns.pairplot()
sns.distplot()
sns.jointplot() : visualiser 2 variables à la fois
    style avec kind : kde, hex

Visualiser des matrices :
sns.heatmap()

Quand utiliser Seaborn :
Data - Exploration Statistique : Vision Globale

Quand utiliser MatPlotLib : 
Fonctions, matrices, etc - Mathématique, science, ingénierie, etc - Graphique spécialisé
"""

import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt 
import seaborn as sns 

iris = pd.read_csv("data-sns/iris.csv")
print(iris.head())

sns.pairplot(iris, hue = 'species') # trace des graphiques avec toutes les relations entres toutes les variables
# hue='variety' : couleur pour chaque variété de fleur (colonnes species) en fonction de toutes les variables du dataset
plt.show()

titanic = sns.load_dataset("titanic")
titanic.drop(["alone", "alive", "who", 'adult_male', "embark_town", 'class'], axis=1, inplace=True)
titanic.dropna(axis=0, inplace=True)
print(titanic.head())

sns.catplot(x='pclass', y='age', data=titanic, hue='sex')
plt.show()
sns.boxplot(x='pclass', y='age', data=titanic, hue='sex')
plt.show()
sns.distplot(titanic['fare'])
plt.show()
sns.jointplot(x='age', y='fare', data=titanic, kind='hex') # kind : style
plt.show()

titanic[:] = titanic.apply(lambda c: c.astype('category').cat.codes) # convertie chaque catégorie de chaque colonne en valeur numérique
# apply : applique sur chaque colonne la fonction lambda de paramètre 'c'
# astype : compte le nombre de fois que chaque catégories apparaissent dans la colonne 'c'
# cat.codes : les converties en valeur numérique

sns.heatmap(titanic.corr()) # visualiser les corrélations dans le titanic
plt.show()
"""
Pandas permet de manipuler des données.
DataFrame : tableau ressemblant à un tableau excel, qui contient un dataset. C'est un dictionnaire de séries.
Série : colonne d'un dataframe, c'est un tableau numpy à une dimension, dans lequel une colonne 'index' est rajouté.
On peut assemblé des séries quand elle partage le même index.


data.shape : renvoie la taille du dataset 'data'
data.colums : renvoie le nom de toutes les colonnes
data.head() : renvoie les premières lignes du dataset

data.describe() : produit les statistiques de bases pour chaque colonne

data.fillna(data['column'].mean()) : remplie les données manquante, mais ça va corrompre le dataset
data.drop(['column', 'column2], axis=1) : permet de supprimer les colonnes portant le nom de 'column' et 'column2', selon l'axe 1 (colonnes)
data.dropna(axis=0) : supprime les lignes qui ont des données manquantes

data['column'].value_counts() : compte la proportion de chaque valeur de la colonne 'column'
data['sex'] : analyse en regroupant selon la colonne 'sex'
data.set_index('name') : change l'index du DataFrame, avec le nom des passagés

Pandas travaille en collaboration avec MatPlotLib : 
.plot.bar() : crée un graphique de bar
.hist() : crée un histogramme

L'indexing, le masking et le boolean indexing sont aussi possible avec les DataFrames, car une série = ndarray
data['age'][0:10] : affiche les 10 premiers éléments de la série 'age'.
data['age'] < 18 : crée un mask de valeurs booléennes
data[data['age'] < 18] : boolean indexing

data.iloc[0, 0] : ndarray[0, 0] : indexing
data.loc[0:2, 'age'] : renvoie les 3 premières valeurs de la série 'age'
data.loc[0:2, ['age', 'sex']] : renvoie les 3 premières valeurs des séries 'age' et 'sex'
data.loc[0:2, :] : renvoie les 3 premières valeurs de toutes les séries (colonnes)

data['age'].map(function) : 'map' permet d'apliquer une fonction sur chaque élément d'une colonne
data.apply(function) : applique une fonction sur chaque élément d'un Dataframe

Transformer des catégories en données numériques :
data['sex'].map( {'male':0, 'female':1} ) : associe 0 à 'male' et 1 à 'female'
data['sex'].replace( ['male', 'female'], [0, 1]) : remplace 'male' et 'female' par 0 et 1
data['sex'].astype('category').cat.codes : 'astype' compte le nombre de fois que chaque catégorie apparaissent, 'cat.codes' les converties en valeurs numériques
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_excel("titanic.xls") # lis le dataset en fichier excel 'titanic.xls'
print(data.shape)

data = data.drop(['name', 'sibsp', 'parch', 'ticket', 'fare', 'cabin', 'embarked', 'boat', 'body', 'home.dest'], axis=1) # supprime toutes ces colonnes
print(data.head())
print(data.describe())

data = data.dropna(axis=0) # supprime les lignes qui ont des données manquantes
print(data.shape)

print(data.groupby(['sex', 'pclass']).mean()) # renvoie la moyenne de chaque colonne, en regroupant les personnes par leur sexe ET leur classe
print(data[data['age'] < 18].groupby(['sex', 'pclass']).mean()) # renvoie la moyenne de tous les passagés mineur (age<18), regroupé par leur sexe et classe
print(data.loc[1:3, ['age', 'sex']]) # renvoie les valeurs 1 à 3 des colonnes 'age' et 'sex'

plt.figure(figsize=(6,8))

plt.subplot(2,1,1)
data['pclass'].value_counts().plot.bar() # crée un graphique de barre de la proportion des personnes qui étaient en 1er, 2ème et 3ème classe

plt.subplot(2,1,2)
data['age'].hist() # crée un histogramme de la répartition des âges

plt.show()
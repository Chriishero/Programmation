"""
make_column_transformer : sélectionne les variables de façon explicite
    make_column_transformer((StandardScaler()), ['age', 'fare']) : applique la transformation uniquement sur les colonnes 'age' et 'fare'

make_column_selector : sélectionne les variables selon le type indiqué
    make_column_selector(dtype_include=type, dtype_exclude=type, pattern=regex)
    np.number : variables numériques
    object : variables catégorielles

make_union : crée des pipelines parallèles, les résultats sont concaténés à la sortie du transformer
    make_union(StandardScaler(), Binarizer()) : la transformation renverra 2x plus de colonnes, celle des variables standardisé, et celle des variables discrétisés
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.pipeline import make_pipeline, make_union
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.impute import SimpleImputer # remplace les valeurs manquantes
from sklearn.linear_model import SGDClassifier
from sklearn.compose import make_column_transformer, make_column_selector
import seaborn as sns

titanic = sns.load_dataset("titanic")
y = titanic['survived']
X = titanic.drop("survived", axis=1)

numerical_features = ['pclass', 'age', "fare"] # variable numérique sur lesquels une certaine transformation sera effectué
numerical_features = make_column_selector(dtype_include=np.number) # sélectionne les variables numériques
categorical_features = ["sex", "deck", "alone"]
categorical_features = make_column_selector(dtype_exclude=np.number) # sélectionne les variables non numériques

numerical_pipeline = make_pipeline(SimpleImputer(), StandardScaler())
categorical_pipeline = make_pipeline(SimpleImputer(strategy='most_frequent'), OneHotEncoder())
# SimpleInputer(strategy='most_frequent') : remplace les valeurs manquantes par les valeurs les plus fréquentes

preprocessor = make_column_transformer((numerical_pipeline, numerical_features), # assemble les 2 pipelines avec les colonnes correspondantes
                                       (categorical_pipeline, categorical_features))

model = make_pipeline(preprocessor, SGDClassifier()) # utilise le column transformer 'transformer'
print(model.fit(X, y))
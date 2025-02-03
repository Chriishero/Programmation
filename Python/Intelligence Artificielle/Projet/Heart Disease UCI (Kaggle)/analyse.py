"""
AIDE À L'ANALYSE : 
https://www.kaggle.com/code/pmarcelino/comprehensive-data-exploration-with-python/notebook

1. Exploratory Data Analysis
## Checklist de base 
    Analyse de Forme : 
        Variable target : num
        Lignes et colonnes : (920, 16)
        Types de variables : object     8
                            float64    5
                            int64      3
        Analyse de valeurs manquantes : 
            - ca          611  0.664130
              thal        486  0.528261
              slope       309  0.335870
            - Le reste à moins de 10% (100) de valeurs manquantes
            - Valeurs manquantes corrélé entre 'thalch', 'exang', 'oldpeak', 'trestbps'

    Analyse de Fond :
        Visualisation de la target :
            - 0    0.446739
              1    0.288043
              2    0.118478
              3    0.116304
              4    0.030435
            - On peut supposer que le chiffre correspond au degré de gravité de la maladie
            - Skewness :  0.9688800484130079
              Kurtosis :  -0.104325193611428
        Signification des variables :
            - variables continues : - peu de skewness, 'ca, oldpeak, trestbps' ont entre 0.21 et 1.16
                                    - 'oldpeak' a peu de variation
                                    - 'ca' et 'chaul' ont beaucoup de donnée = 0
            - variables qualitatives : - plus grande proportion d'hommes que de femmes (78% d'homme)
                                       - 'cp' : grosse proportion d'asymptomatiques
                                       - 'fbs' : quasiment que des valeurs nulles (700 : 0 et 150 : 1)
                                       - 'restecg' : beaucoup de 'normal'
                                       - 'slope' : très peu de downsloping
                                       - 'thal' : très peu de fixed defect (aucune idée de la signification)
                                       - skewness : {'restecg': 0.7056763978954366, 
                                                    'cp': 0.6945563740165083, 
                                                    'slope': 0.008685866847171035, 
                                                    'dataset': -0.37096506624815223, 
                                                    'thal': -0.7053649006572325}
                                      - Skewness positive : asymétrique | négative : faible proportion de certaines valeurs
        Relation Variables / Target : 
            - la target semble corrélé à 'age', 'ca' et 'oldpeak'
            - si 'exang' est False, 'num' sera majoritairement = 0 (abscence de maladie cardiaque)
            - 'sex' pourrait être corrélée, mais il faut prendre, en compte la plus grande proportion d'homme
            - 'dataset' pourrait être corrélée, mais l'endroit d'étude ne devrait avoir aucun rapport avec une maladie cardiaque
            - 'cp' : il y a une plus grande proportion d'asymptomatique, mais bizarrement ils sont en majorité malade
            - 'thal' semble corrélée
            - 'fbs', 'restecg', 'slope' ne semble pas corrélée

## Analyse plus détaillée
    Relation Variables / Variables :
        - Quantitatives/Quantitatives : 
            - 'ca' semble corrélé à 'oldpeak' et 'age'
        - Qualitatives/Qualitatives : 
            - elles semblent quasiment toutes corrélées entre elles
            - 'fbs' non corrélée avec 'cp' et 'exang'
            - 'restecg' non corrrélée avec 'sex' et 'slope' mais possible variable importante (fréquence au repos)
            - 'slope' non corrélée avec 'restecg' uniquement
        - Quantitatives/Qualitatives :
            - 'ca' corrélée avec 'fbs', 'cp', 'exang', 'thal'

        - A absolument garder : 'oldpeak', 'age', 'exang', 'thal' (corrélée avec target) |
                                'ca', 'restecg', 'slope', 'fbs'

    Outliers : 
        - trestbps : 753
        - chol : 546

    Normality :
        - [ca, oldpeak, chol] anormal, il faudra tester des transformation lors du preprocessing

    Homoscedasticity (variables dépendantes qui montrent des niveaux égaux de variances parmis la 
                        range de predictor variables):
        - idem

## Hypothèses nulle (H0) :
    - 
"""

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from scipy import stats # probplot
from scipy.stats import norm, skew, chi2_contingency
from sklearn.preprocessing import OneHotEncoder, StandardScaler, MinMaxScaler, RobustScaler

pd.set_option("display.max_row", 111)
pd.set_option("display.max_columns", 111)
dataset = pd.read_csv("heart_disease_uci.csv")
df = dataset.copy()
df = df.drop("id", axis=1)

total_nan = df.isna().sum().sort_values(ascending=False)
percent_nan = (df.isna().sum()/df.shape[0]).sort_values(ascending=False)
missing_data = pd.concat([total_nan, percent_nan], axis=1, keys=["Total", "Percent"])
print("NaN : ", missing_data)

#df = df[df.columns[df.isna().sum()/df.shape[0] < 0.1]]

plt.figure(figsize=(12, 8))
sns.heatmap(df.isna(), cbar=False)

# Visualisation Target
print(df["num"].value_counts(normalize=True))
#plt.figure()
#sns.distplot(df["num"], fit=norm)
print("Skewness : ", df["num"].skew())
print("Kurtosis : ", df["num"].kurt())

continuous_var = df.select_dtypes(include=["float64", "int64"], exclude=['object', 'category']).columns
continuous_var = continuous_var.drop("num")
qualitativ_var = df.select_dtypes(include=["object"]).columns

# Signification Variables Continues
"""#sns.pairplot(df[continuous_var], height=2.5)
continuous_skewness = df[continuous_var].skew().sort_values(ascending=False)
for col in continuous_var:
    sns.displot(df[col])

# Signification Variables Qualitatives
sns.pairplot(df[qualitativ_var], height=2.5)

qualitativ_skewness = {}
for col in qualitativ_var:
    sns.displot(df[col])
    
    category_counts = df[col].value_counts()
    qualitativ_skewness[col] = skew(category_counts.values)

qualitativ_skewness = dict(sorted(qualitativ_skewness.items(), key=lambda x: x[1], reverse=True))
# key=lambda x: x[1] : trie les éléments en fonction de leur deuxième valeur (skewness)
print(qualitativ_skewness)"""

# Relation Variables/Target
plt.figure()
sns.heatmap(df[continuous_var].corr(), annot=True) # 'annot=True' affiche la corrélation dans chaque case

df["a une maladie cardiaque"] = (df["num"] > 0).astype(int)
"""
for col in qualitativ_var:
    plt.figure()
    sns.countplot(data=df, x=col, hue='a une maladie cardiaque', palette='coolwarm')"""


# Relation Feature/Feature
"""
# Calcule Cramèr's V
def cramers_v(confusion_matrix):
    chi2, p, dof, expected = chi2_contingency(confusion_matrix)
    n = confusion_matrix.sum()
    return np.sqrt(chi2 / (n * (min(confusion_matrix.shape) - 1)))

chi2_results = {}
cramers_v_results = {}

for col1 in qualitativ_var:
    for col2 in qualitativ_var:
        if col1 != col2: # évite de tester les 2 mêmes colonnes 
            df_test = df.copy()
            df_test = df_test.dropna(axis=0)
            contigence_table = pd.crosstab(df[col1], df[col2])
            contigence_table = contigence_table.dropna(axis=0)

            # Test de chi2
            chi2, p, dof, excepted = chi2_contingency(contigence_table)
            chi2_results[(col1, col2)] = p

            # Cramèr's V
            cramers_v_results[(col1, col2)] = cramers_v(contigence_table)

print("Résultat du test de chi2 (p-values) : ")
for pair, p_val in chi2_results.items():
    print(f"{pair}: p_values = {p_val}")

print("Résultat du test de Cramèr's V: ")
for pair, v_val in cramers_v_results.items():
    print(f"{pair}: {df[pair[1]].value_counts()} : Cramèr's V = {v_val}")


def cramers_v(confusion_matrix):
    chi2, p, dof, expected = chi2_contingency(confusion_matrix)
    n = confusion_matrix.sum()
    return np.sqrt(chi2 / (n * (min(confusion_matrix.shape) - 1)))

col2 = 'slope'
for col1 in qualitativ_var:
    if col1 != col2:  # Éviter les paires identiques
        # Créer un tableau croisé (contingency table)
        contingency_table = pd.crosstab(df[col1], df[col2])
        contingency_table = contingency_table.dropna(axis=1)

        # Afficher la carte thermique
        plt.figure(figsize=(8, 6))
        sns.heatmap(contingency_table, annot=True, cmap="Blues", fmt="d", cbar=False)
        plt.title(f"Matrice de confusion entre '{col1}' et '{col2}'")
        plt.xlabel(col2)
        plt.ylabel(col1)

        chi2, p, dof, excepted = chi2_contingency(contingency_table)
        if p > 0.05:
            print(f"{col1} - {col2} (NOcorrélée) : chi2 : ", p)"""

# Outliers
sns.pairplot(df[continuous_var], height=2.5)
print(df[df["trestbps"] < 50].index) # affiche l'index des outliers
print(df[df["chol"] > 600].index)

# Normality
print(continuous_var)
anormality_cols = ["ca", "oldpeak", "chol"]

for col in continuous_var:
    plt.figure()
    sns.distplot(df[col], fit=norm)
    plt.figure()
    stats.probplot(df[col], plot=plt)

plt.show()
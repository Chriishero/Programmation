"""
1. Exploratory Data Analysis
## Checklist de base 
    Analyse de Forme : 
        Variable target : SARS-Cov-2 exam result
        Lignes et colonnes : (5644, 111)
        Types de variables : 
            - float64    70
            - object     37
            - int64       4
        Analyse de valeurs manquantes : 
            - moitié de variables > 90% de NaN
            - 2 groupes de données 76% -> Test viral
            - 89% -> taux sanguins

    Analyse de Fond :
        Visualisation de la target :
            - 10% de positif
        Signification des variables :
            - variables continues standardisées, skewed (pas asymétriques), test sanguin
            - age quantile : difficile d'interprétation, données traités, aucune information sur cette variable
            - variable qualitative : binaire (0, 1), viral, Rhinovirus semble très élevé
        Relation Variables / Target : 
            - Target / Blood : les taux de Monocytes, Platelets, Leukocytes semblent liés au covid-19 -> hypothèse à tester
            - Target / Age : individus à faible âge très peu contaminés? -> ATTENTION on connait pas l'age, ni de quand date le dataset.
                                Mais peu être intéressant à comparer aux résultats de tests sanguins.
            - Target / Viral : les doubles maladies sont très rare. Rhinovirus/Enterovirus positif - covid-19 - negatif ? -> hypothèse à tester ? 
                                Mais on peut avoir 2 virus -> peut n'avoir aucun lien avec le covid

## Analyse plus détaillée
    Relation Variables / Variables :
        - blood_data / blood_data : certaines variables sontr très corrélées : +0.9 (a surveiller plus tard)
        - blood_data / age : très faible corrélation entre âge et taux sanguins
        - viral / viral : influenza rapid test donne de mauvais résultats, il faudra peut-être laisser tomber
        - relation maladie / blood data : les taux sanguins entre malades et covid-19 sont différents
        - relation hospitalisation / est malade : 
        - relation hospitalisation / blood : intéressant dans le cas où on peut prédire dans quelle service un patient devrait aller
    NaN analyse : viral : 1350(92/8), blood : 600(87/13), both : 90

## Hypothèses nulle (H0) :
    - Les invidividus atteints du covid-19 ont des taux de Leukocytes, Monocytes et Platelets significativement différents
        - H0 = Les taux moyens sont ÉGAUX chez les individus positifs et négatifs : rejeté
    - Les individus atteints d'une quelconques maladie ont des taux significativement différents
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from scipy.stats import ttest_ind # test de Student

pd.set_option("display.max_row", 111) # affiche toutes les lignes
pd.set_option("display.max_columns", 111)
dataset = pd.read_excel("dataset.xlsx")

df = dataset.copy()
print(df.dtypes.value_counts()) # compte le nombre de variables pour chaque types
print(df.head())
print((df.isna().sum()/df.shape[0]).sort_values(ascending=True)) # affiche dans l'ordre croissant la proportion des valeurs manquantes de chaque variables.

df = df[df.columns[df.isna().sum()/df.shape[0] < 0.9]] # garde seulement les variables (colonnes) qui possède un taux de NaN < 90%
df = df.drop("Patient ID", axis=1)
print(df.shape)

print(df["SARS-Cov-2 exam result"].value_counts(normalize=True)) # normalise=True affiche en pourcentage

"""
plt.figure(figsize=(20,10))
sns.heatmap(df.isna(), cbar=False)

for col in df.select_dtypes('float'): # variables continues
    plt.figure()
    sns.distplot(df[col])

plt.figure()
sns.distplot(df["Patient age quantile"])

for col in df.select_dtypes('object'): # variables discrètes
    print(f'{col :-<50}, {df[col].unique()}') # 'unique' affiche les différentes catégories de chaque variable
    # col :-<50 : crée une marge de moins de 50 '-'
    plt.figure()
    df[col].value_counts().plot.pie()"""


missing_rate = df.isna().sum()/df.shape[0]
# Sous-ensembles positifs et négatifs
positive_df = df[df["SARS-Cov-2 exam result"] == "positive"] # isole les patients positif
negative_df = df[df["SARS-Cov-2 exam result"] == "negative"]

# Sous-ensembles Blood et Viral
blood_columns = df.columns[(missing_rate < 0.9) & (missing_rate > 0.88)] # toutes les variables de type taux sangin
viral_columns = df.columns[(missing_rate < 0.88) & (missing_rate > 0.75)] # toutes les variables de type test viral

"""
# Relation Target / Blood
for col in blood_columns:
    plt.figure()
    sns.distplot(positive_df[col], label='positive')
    sns.distplot(negative_df[col], label='negative')
    plt.legend()

# Relation Target / Blood
sns.countplot(x='Patient age quantile', hue='SARS-Cov-2 exam result', data=df)

# Relation Target / Viral
for col in viral_columns:
    plt.figure()
    sns.heatmap(pd.crosstab(df['SARS-Cov-2 exam result'], df[col]), annot=True, fmt='d') # affiche les croisements entre les cas positif/negatif de ces 2 variables qualitatives
    # annot=True : affiche les quantités de chaque variables
    # fmt='d' : affiche les nombres en entier

# Relation Taux Sanguin
sns.heatmap(df[blood_columns].corr()) # tableau de corrélation entre toutes les variables de taux sanguin
sns.clustermap(df[blood_columns].corr()) # même chose en regroupant les variables par cluster

# Relation Age / Sang
for col in blood_columns:
    plt.figure()
    sns.lmplot(x="Patient age quantile", y=col, hue='SARS-Cov-2 exam result', data=df) # visualise une courbe de régression dans un nuage de point entre l'age et les taux sanguins
    # hue='SARS-Cov-2 exam result' : discrimination en fonction des résultats positifs ou négatifs

df_numeric = df.select_dtypes(include=[float, int]) # sélectionne uniquement les valeurs numériques
print(df_numeric.corr()["Patient age quantile"].sort_values()) # affiche les corrélations entre l'âge et les taux sanguins

# Relation Influenza / Rapid test
print("\nRelation Influenza / Rapid test")
print(pd.crosstab(df["Influenza A"], df["Influenza A, rapid test"]))
print(pd.crosstab(df["Influenza B"], df["Influenza B, rapid test"]))

# Relation Viral / Sanguin
df["est malade"] = np.sum(df[viral_columns[:-2]] == "detected", axis=1) >= 1 # création d'une nouvelle variable qui dit si un patient est testé positif à au moins une maladie ou non
malade_df = df[df["est malade"] == True] # isole les patients positif
non_malade_df = df[df["est malade"] == False]

for col in blood_columns:
    plt.figure()
    sns.distplot(malade_df[col], label='malade')
    sns.distplot(non_malade_df[col], label='non malade')
    plt.legend()

# Relation Hospitalisation / blood
def hospitalisation(df): # retourne une valeur en fonction de l'état d'hospitalisation du patient
    if df["Patient addmited to regular ward (1=yes, 0=no)"] == 1:
        return 'surveillance'
    elif df["Patient addmited to semi-intensive unit (1=yes, 0=no)"] == 1:
        return 'soins semi-intensives'
    elif df["Patient addmited to intensive care unit (1=yes, 0=no)"] == 1:
        return "soins intensifs"
    else:
        return 'inconnu'
    
df["statut"] = df.apply(hospitalisation, axis=1) # applique la fonction sur l'axe 1 (ligne) de la nouvelle variable 'statut'
print(df['statut'].head())

for col in blood_columns:
    plt.figure()
    for cat in df["statut"].unique(): # crée de nouveaux distplot dans lesquels on va itéré dans les différentes catégories de 'statut'
        sns.distplot(df[df["statut"] == cat][col], label=cat)
        # df["statut"] == cat : filtre 'statut' = cat 
        # [col] : sélectionne uniquement la colonne de taux sanguins
    plt.legend()
"""

# NaN analyse
print(df[viral_columns].count())
print(df[blood_columns].count())

df1 = df[viral_columns[:-2]]
df1["covid"] = df["SARS-Cov-2 exam result"]
print(df1.dropna()["covid"].value_counts(normalize=True)) # vérifie les proportions de positifs et négatifs au covid en supprimant toutes les valeurs NaN des virals

df1 = df[blood_columns[:-2]]
df1["covid"] = df["SARS-Cov-2 exam result"]
print(df1.dropna()["covid"].value_counts(normalize=True))  # vérifie les proportions de positifs et négatifs au covid en supprimant toutes les valeurs NaN des taux sanguins

# Test de Student
print(positive_df.shape)
print(negative_df.shape)
balanced_neg = negative_df.sample(positive_df.shape[0]) # 558 (nombre de lignes de 'positive_df') échantillons extraient au hasard de 'negative_df'

def t_test(col):
    alpha = 0.02
    stat, p = ttest_ind(balanced_neg[col].dropna(), positive_df[col].dropna()) # Si la moyenne entre 2 distributions est significativement différentes
    if p < alpha:
        return "H0 Rejetée"
    else:
        return 0
    
for col in blood_columns:
    print(f"{col :-<50} {t_test(col)}")

plt.show()
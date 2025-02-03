"""
AIDE À L'ANALYSE : 
https://www.kaggle.com/code/pmarcelino/comprehensive-data-exploration-with-python/notebook

1. Exploratory Data Analysis
## Checklist de base 
    Analyse de Forme : 
        Variable target : count
        Lignes et colonnes : (10886, 12)
        Types de variables : 
            int64      8
            float64    3
            object : datatime (devenu index)

        Analyse de valeurs manquantes : 
            - aucune valeur manquante

    Analyse de Fond :
        Visualisation de la target :
            - Skewness : 1.2420662117180776
            - Kurtosis : 1.3000929518398334
            - Variance : 32813.31315347235
            - Semble corrélée au datetime, timeseries nécessaire

        Signification des variables :
            - Continues : 'temp, atemp, humidity, windspeed, casual, registered'
                - 'casual' et 'registered' ne valent pas la peine, leurs assemblement donne 'count'
                - Skewness : 
                    temp         0.003691
                    atemp       -0.102560
                    humidity    -0.086335
                    windspeed    0.588767
                - Kurtosis : 
                    temp        -0.914530
                    atemp       -0.850076
                    humidity    -0.759818
                    windspeed    0.630133
                - Variance : 
                    temp            60.708872
                    atemp           71.818856
                    humidity       370.371306
                    windspeed       66.659670

            - Catégorielles : 'season, holiday, working, day, weather'
                - Skewness : 
                    season       -0.007076
                    holiday       5.660517
                    workingday   -0.776163
                    weather       1.243484
                - Kurtosis : 
                    season        -1.355661
                    holiday       30.046975
                    workingday    -1.397828
                    weather        0.395533
                - Variance : 
                    season        1.245845
                    holiday       0.027755
                    workingday    0.217304
                    weather       0.401751
                - holiday et working day : distribution déséquilibré
                - weather : grand majorité de 1 | minorité de 3 | un seul de 4
                
        Relation Variables / Target : 
            - Corrélation : au dessus de 0.1%
                season :  0.1634390165763616
                temp :  0.39445364496724916
                atemp :  0.38978443662697654
                windspeed :  0.10136947021033275
            - datetime corrélée 

## Analyse plus détaillée
    Relation Variables / Variables :
        - temp et atemp veulent dire la même chose, une seule sera utile à garder
        - Corrélation : 
            - season : temp, atemp, humidity
            - weather : humidity

    NaN analyse : idem que plus haut

    Outliers : 
        - windspeed : '2011-07-03 17:00:00', '2011-07-03 18:00:00'
        - weather : '2012-01-09 18:00:00' (l'unique 4)

    Normality :
        - toutes les variables sont anormal
        - Meilleur transformation : 
            - count : sqrt
            - temp : sqrt
            - atemp : sqrt
            - humidity : aucune
            - windspeed : yeo-johnson

    Homoscedasticity (variables dépendantes qui montrent des niveaux égaux de variances parmis la 
                        range de predictor variables):
        - count, temp, atemp font de l'hétéroscedasticity
        - Meilleur transformation : 
            - count : sqrt
            - temp : sqrt
            - atemp : sqrt

## Hypothèses nulle (H0) :
    - 
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import PowerTransformer
from scipy import stats # probplot
from scipy.stats import norm, boxcox
import ydata_profiling as pp

dataset = pd.read_csv("set/train.csv", index_col="datetime", parse_dates=True)
df = dataset.copy()


profile = pp.ProfileReport(df, title="Bike Sharing Demand Report",  # Titre du rapport
                           correlations={
                               "pearson": {"calculate": True},  # Calculer les corrélations de Pearson
                               "spearman": {"calculate": True},  # Calculer les corrélations de Spearman
                               "kendall": {"calculate": True},  # Calculer les corrélations de Kendall
                               "auto": {"calculate": True}      # Calculer la corrélation automatique
                           },
                           explorative=True,  # Active les options exploratoires
                           missing_diagrams={"heatmap": True, "dendrogram": True},  # Diagrammes de valeurs manquantes
                           interactions={"continuous": True, "categorical": True},  # Interactions continues et catégorielles
                           minimal=False,  # Plus de détails, évite la version minimaliste
                           duplicates={"count": True, "list": True},  # Compter et lister les doublons
                           infer_dtypes=True,  # Déduire les types de données
                          )

profile.to_file("bike_sharing_demand_report.html")  # Sauvegarde du rapport

skewness = df.skew().sort_values(ascending=False)
kurtosis = df.kurt().sort_values(ascending=False)
variance = df.var().sort_values(ascending=False)

# Visualisation Target
print(skewness["count"])
print(kurtosis["count"])
print(variance["count"])
plt.figure()
plt.plot(df.index, df["count"])

# Signification Variables
continuous_var = df.drop(["season", "holiday", "workingday", "weather", "casual", "registered", "count"], axis=1).columns
categorial_var = ["season", "holiday", "workingday", "weather"]

print("skew : ", skewness[continuous_var])
print("kurt : ", kurtosis[continuous_var])
print("var : ", variance[continuous_var])

"""for col in df[categorial_var]:
    plt.figure()
    df[col].value_counts().plot(kind='bar')
    plt.title(f"Distribution des catégories de {col}")"""

# Relation Variables / Targets
for col in df.columns:
    print(f"count / {col} : ", df["count"].corr(df[col]))

# Relation Variables / Variables
plt.figure(figsize=(12,8))
sns.heatmap(df.corr(), annot=True)

# Outliers 
#sns.pairplot(df, height=1)
print(df[df["windspeed"] > 55].index)
print(df[df["weather"] == 4].index)

# Normality / Homoscedasticy
"""
for col in df.columns:
    plt.figure()
    sns.distplot(df[col], fit=norm)
    plt.title(f'{col}')
    plt.figure()
    stats.probplot(df[col], plot=plt)
    plt.title(f'{col}')"""

def math_transform(col): 
    df_transform = pd.DataFrame()
    df_transform[col] = df[col].copy()
    #df_transform[col] = df_transform[col].replace(0, 1)

    try:
        #df_transform[f"{col}_log"] = np.log(df_transform[col])
        print("hey")
    except:
        print("log marche pas")
    try:
        df_transform[f"{col}_sqrt"] = np.sqrt(df_transform[col])
    except:
        print("sqrt marche pas")
    try:
        df_transform[f"{col}_cbrt"] = np.cbrt(df_transform[col]) 
    except:
        print("cbrt marche pas")
    try:
        df_transform[f"{col}_boxcox"], _ = stats.boxcox(df_transform[col] + 1) 
    except:
        print("boxcox marche pas")
    try:
        pt = PowerTransformer(method="yeo-johnson")
        df_transform[f"{col}_yeo-johnson"]= pt.fit_transform(df_transform[col].values.reshape(-1, 1))
    except:
        print("yeo-johnson marche pas")

    for col in df_transform.columns:
        plt.figure()
        sns.distplot(df_transform[col], fit=norm)
        plt.title(f'{col}')
        plt.figure()
        stats.probplot(df_transform[col], plot=plt)
        plt.title(f'{col}')
        plt.figure()
        plt.scatter(df_transform[col], df["count"])
        plt.title(f'Homoscedasticy : {col}')

math_transform("humidity")

plt.show()

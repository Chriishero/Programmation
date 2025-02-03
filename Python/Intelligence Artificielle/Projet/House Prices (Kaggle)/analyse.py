"""
AIDE À L'ANALYSE : 
https://www.kaggle.com/code/pmarcelino/comprehensive-data-exploration-with-python/notebook

1. Exploratory Data Analysis
## Checklist de base 
    Analyse de Forme : 
        Variable target : SalePrice
        Lignes et colonnes : (1460, 81)
        Types de variables : 
            - float64    3
            - object     43
            - int64      35
        Analyse de valeurs manquantes : 
            - 5 variables : +50% de NaN
                MasVnrType       0.597260
                Fence            0.807534
                Alley            0.937671
                MiscFeature      0.963014
                PoolQC           0.995205
            - Autres : +6%
                LotFrontage      0.177397
                FireplaceQu      0.472603
            - Beaucoup de variables ont le même nombres de valeurs manquante, comme GarageX, BsmtX, MasX, elles sont sûrement très similaire, en garder qu'une seule de chaque suffira

    Analyse de Fond :
        Visualisation de la target :
            - valeur numérique variable : régression linéaire nécessaire
            - assez peu de variation : la majorité des prix sont à environ 100k, la majorité est entre 50k et 250
            - Skewness :  1.8828757597682129
            - Kurtosis :  6.536281860064529
        Signification des variables :
            - variables continues : skeweness > 5
                                    MiscVal          24.476794
                                    PoolArea         14.828374
                                    LotArea          12.207688
                                    3SsnPorch        10.304342
                                    LowQualFinSF      9.011341

                                    très peu de variation dans 'MasVnrArea', environ 20 variables dont la variation est quasi nul, mais MiscVal a un très grosse variation comparé aux autres
            - variable qualitative : beaucoup de variables ont une distribution de catégorie très déséquilibré (une seule à la majorité)
        Relation Variables / Target : 
            - il y a de forte corrélation entre les variables et la target, ainsi que de faible (min : -13%, max : 79%)
                Forte : OverallQual, GrLiveArea, TotalBsmtSF
                YearBuilt petite corrélation, analyse de timeseries ?
            - il y a des variables jumelles, qui veulent dire la même chose :
                TotalBsmtSF/1stFloor
                TotRmsAbvGrd/GrLiveArea

        Outliers : 
            - les low outer range sont proche de 0
            - les high outer range peuvent atteindre les 7, sûrement des outliers
            - GrLivArea et TotalBsmtSF contiennent des outliers
                GrLivArea : Id 524 et 1299
                TotalBsmtSF : > 3000

        Normality :
            - SalePrice est asymétrique (un 'np.log' peut résoudre le problème)
            - SalePrice ne suit pas une distribution normal (Q-Q plot) (un 'np.log' peut résoudre le problème)
            - Idem pour GrLivArea
            - TotalBsmtSF est aussi asymétrique mais ne peut pas subire de log à cause de valeur nulle (0)
                Création d'une variable contenant uniquement les valeurs non nulle pour la transformation logarithmique

        Homoscedasticity (variables dépendantes qui montrent des niveaux égaux de variances parmis la 
                          range de predictor variables):
            - Les formes sont (scatter plot):
                - Cones : petites dispersion d'un côté et large de l'autre
                - Diamant : large nombres de points au centre de la distribution
            - La transformation logarithmique à résolu le problème d'homoscedasticity sur SalePrice, GrLivArea
            

## Analyse plus détaillée
    Relation Variables / Variables :
        - Certaines variables sont assez colléré (+60%) : 
    NaN analyse : idem que plus haut

## Hypothèses nulle (H0) :
    - 
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import StandardScaler
from scipy import stats # probplot
from scipy.stats import norm

pd.set_option("display.max_row", 111) # affiche toutes les lignes
pd.set_option("display.max_columns", 111)
dataset = pd.read_csv("train.csv")
df = dataset.copy()

total_nan = df.isnull().sum().sort_values(ascending=False)
percent_nan = (df.isna().sum()/df.shape[0]).sort_values(ascending=False)
missing_data = pd.concat([total_nan, percent_nan], axis=1, keys=["Total", "Percent"])
print("Proporiton de NaN : ", missing_data.head(20))
"""
plt.figure(figsize=(12,8))
sns.heatmap(df.isna(), cbar=False)"""

df = df[df.columns[df.isna().sum()/df.shape[0] < 0.50]] # garde seulement les variables dont le taux de NaN est < 80%
print(df.shape)

# Visualisation Target
"""plt.figure(figsize=(12,6))
sns.histplot(df["SalePrice"], kde=True)
plt.xlabel("SalePrice")
plt.ylabel("Frequence")"""

print("Skewness : ", df["SalePrice"].skew()) 
print("Kurtosis : ", df["SalePrice"].kurt())

# Signification variables quantitatives
continous_vars = df.select_dtypes(include=["float64", "int64"]).columns
#continous_vars = continous_vars.drop("SalePrice")

skewness = df[continous_vars].skew().sort_values(ascending=False) # calcule l'asymétrie de chaque variable
variation = df[continous_vars].var().sort_values(ascending=False) # calcule la variance de chaque variable
"""
plt.figure(figsize=(12,8))
skewness.plot(kind='bar')
plt.title("Asymétrie (Skewness) des variables continues")

plt.figure(figsize=(12,8))
variation.plot(kind='bar')
plt.title("Variance des variables continues")"""

# Signification variables qualitatives
qualitative_vars = df.select_dtypes(include=["object"]).columns

"""for col in qualitative_vars:
    plt.figure()
    df[col].value_counts().plot(kind="bar")
    plt.title(f"Distribution des catégories de : {col}")"""
"""
plt.figure()
data = pd.concat([df['SalePrice'], df["OverallQual"]], axis=1)
sns.boxplot(x="OverallQual", y="SalePrice", data=data)

plt.figure()
data = pd.concat([df['SalePrice'], df["YearBuilt"]], axis=1)
sns.boxplot(x="YearBuilt", y="SalePrice", data=data)
plt.xticks(rotation=90) # tourne les valeurs de l'axe x, on les voit pas sinon
"""

# Corrélation Features/Features
correlations = df[continous_vars].corrwith(df["SalePrice"])
high_correlation_vars = correlations[correlations.abs() > 0.6].index
"""
plt.figure(figsize=(12,10))
correlation_matrix = df[continous_vars].corr()
sns.heatmap(correlation_matrix, cmap='coolwarm', annot=False, fmt='.2f')
plt.title("Matrice de corrélation entre les variables continues")

plt.figure(figsize=(12,10))
k = 10 # 10 variables pour la heatmap zoomé
cols = correlation_matrix.nlargest(k, "SalePrice")["SalePrice"].index
cm = np.corrcoef(df[cols].values.T)
sns.set(font_scale=1.25)
sns.heatmap(cm, square=True, fmt=".2f", annot_kws={"size" : 10}, yticklabels=cols.values, xticklabels=cols.values)
"""

"""
# Corrélation Target/Feature
for col in high_correlation_vars:
    corr = df["SalePrice"].corr(df[col])
    print(corr)
    plt.figure()
    plt.scatter(df["SalePrice"], df[col])
    plt.xlabel(col)
    plt.ylabel("SalePrice")
    plt.title(corr)
    plt.legend()"""

# Outliers 
"""saleprice_scaled = StandardScaler().fit_transform(df["SalePrice"].to_numpy()[:, np.newaxis])
    # transforme le dataframe en tableau numpy pour manipuler les données
    # [:, np.newaxis] : transforme le tableau 1D (n,) en tableau 2D (n, 1) en ajoutant une colonne de biais, car fit_transforme nécessite un tableau 2D

low_range = saleprice_scaled[saleprice_scaled[:, 0].argsort()][:10] # extrait les 10 permières valeurs du tableau trié de la 1er colonne 
high_range = saleprice_scaled[saleprice_scaled[:, 0].argsort()][-10:] # extrait les 10 dernières valeurs du tableau trié de la 1er colonne 
print("Range des outliers (low) : ")
print(low_range)
print("Range des outliers (high) : ")
print(high_range)

cols = ["SalePrice", "OverallQual", "GrLivArea", "GarageCars", "TotalBsmtSF", "FullBath", "YearBuilt"]
sns.pairplot(df[cols], height=2.5)

print(df[df["GrLivArea"] > 4500]["Id"]) # affiche l'Id des outliers
print(df[df["TotalBsmtSF"] > 3000]["Id"])
"""

# Normality
"""df["SalePrice"] = np.log(df["SalePrice"]) # applique la transformation logarithmique
plt.figure()
sns.distplot(df["SalePrice"], fit=norm) # 'fit=norm' trace une courbe d'ajustement avec une distribution normal (norm)
plt.figure()
stats.probplot(df["SalePrice"], plot=plt) # graphique de probabilité quantile-quantile, compare les données observés avec la distribution théorique

df["GrLivArea"] = np.log(df["GrLivArea"]) # applique la transformation logarithmique
plt.figure()
sns.distplot(df["GrLivArea"], fit=norm) # 'fit=norm' trace une courbe d'ajustement avec une distribution normal (norm)
plt.figure()
stats.probplot(df["GrLivArea"], plot=plt) # graphique de probabilité quantile-quantile, compare les données observés avec la distribution théorique
"""
df["HasBsmt"] = pd.Series(len(df["TotalBsmtSF"]), index=df.index)
df["HasBsmt"] = 0
df.loc[df["TotalBsmtSF"] > 0, "HasBsmt"] = 1 # crée un masque binaire, si area > 0 alors c'est 1, sinon 0
df.loc[df["HasBsmt"] == 1, "TotalBsmtSF"] = np.log(df["TotalBsmtSF"])

plt.figure()
sns.distplot(df[df["TotalBsmtSF"] > 0]["TotalBsmtSF"], fit=norm) # 'fit=norm' trace une courbe d'ajustement avec une distribution normal (norm)
plt.figure()
stats.probplot(df[df["TotalBsmtSF"] > 0]["TotalBsmtSF"], plot=plt) # graphique de probabilité quantile-quantile, compare les données observés avec la distribution théorique


# Homoscedasticity
plt.figure()
plt.scatter(df["GrLivArea"], df["SalePrice"])
plt.title("Sans log transformation")
plt.xlabel("GrLivArea")
plt.ylabel("SalePrice")

df["SalePrice"] = np.log(df["SalePrice"]) # applique la transformation logarithmique
df["GrLivArea"] = np.log(df["GrLivArea"]) # applique la transformation logarithmique
plt.figure()
plt.scatter(df["GrLivArea"], df["SalePrice"])
plt.title("Avec log transformation")
plt.xlabel("GrLivArea")
plt.ylabel("SalePrice")

plt.figure()
df["TotalBsmtSF"] = np.log(df["TotalBsmtSF"])
plt.scatter(df["TotalBsmtSF"], df["SalePrice"])
plt.title("Avec log transformation")
plt.xlabel("TotalBsmtSF")
plt.ylabel("SalePrice")



plt.show()

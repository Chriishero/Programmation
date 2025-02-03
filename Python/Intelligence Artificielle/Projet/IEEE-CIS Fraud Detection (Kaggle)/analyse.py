"""
AIDE À L'ANALYSE : 
https://www.kaggle.com/code/pmarcelino/comprehensive-data-exploration-with-python/notebook
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from sklearn.preprocessing import PowerTransformer, StandardScaler
from statsmodels.stats.outliers_influence import variance_inflation_factor
from statsmodels.tools.tools import add_constant    
import scipy.stats as stats
import ydata_profiling as pp
import missingno as msno
from sklearn.ensemble import IsolationForest
from sklearn.preprocessing import StandardScaler

dataset_id = pd.read_csv("set/train_identity.csv")
dataset_trans = pd.read_csv("set/train_transaction.csv")

df_id = dataset_id.copy()
df_trans = dataset_trans.copy()
df = pd.concat([df_id, df_trans], axis=1)

# Supprimer les colonnes dupliquées
df = df.loc[:, ~df.columns.duplicated()]

#profile = pp.ProfileReport(df, title="IEE-CIS Fraud Detection", correlations={"auto": {"calculate": False}}, explorative=True, minimal=True)
#profile.to_file("fraud_detection_report.html")

df["indice"] = df.index

"""Analyse de Forme"""
missing_value = df.isna().sum()/df.shape[0]

#print(df["isFraud"].mean())
#print(df["isFraud"].std())
#print(missing_value[(missing_value >= 0.1) & (missing_value <= 0.5)])
df = df[df.columns[missing_value < 0.70]]
print(df.shape)

"""Analyse de Fond"""
numerical_features = df.select_dtypes(exclude="object").columns
qualitative_features = df.select_dtypes(include="object").columns

skewness = df[numerical_features].skew().sort_values(ascending=False)
kurtosis = df[numerical_features].kurt().sort_values(ascending=False)
variance = df[numerical_features].var().sort_values(ascending=False)

# Visualisation de la Target
print(skewness["isFraud"])
print(kurtosis["isFraud"])
print(variance["isFraud"])

# Signification Variables Continues
important_num_features = ["TransactionDT", "TransactionAmt", "dist1"]
for col in df.columns:
    if col.startswith("C") | col.startswith("D"):
        important_num_features.append(col)
print(important_num_features)
print("Skewness num features : ", skewness[important_num_features][ (skewness[important_num_features] > 1) | (skewness[important_num_features] < -1) ])
print("Kurtosis num features : ", kurtosis[important_num_features][ (kurtosis[important_num_features] > 3) | (kurtosis[important_num_features] < -1) ])
print("Variance num features : ", variance[important_num_features])

# Signification Variables Catégorielles 
important_cat_features = ["addr1", "addr2"]
for col in df.columns:
    if col.startswith("card"):
        important_cat_features.append(col)
important_cat_features.remove("card6")
important_cat_features.remove("card4")

print("Skewness num features : ", skewness[important_cat_features][ (skewness[important_cat_features] > 1) | (skewness[important_cat_features] < -1) ])
print("Kurtosis num features : ", kurtosis[important_cat_features][ (kurtosis[important_cat_features] > 3) | (kurtosis[important_cat_features] < -1) ])
print("Variance num features : ", variance[important_cat_features])

important_cat_features.append("card4")
important_cat_features.append("card6")
print(important_cat_features)

# Relation Variables Numériques / Target
for col in numerical_features:
    if abs(df["isFraud"].corr(df[col])) > 0.1:
        print(f"isFraud / {col} : ", df["isFraud"].corr(df[col]))

# Relation Variables Qualitatives / Target
def cramers_v(confusion_matrix):
    chi2, p, dof, expected = stats.chi2_contingency(confusion_matrix)
    n = confusion_matrix.sum()
    return np.sqrt(chi2 / (n * (min(confusion_matrix.shape) - 1)))

for col in qualitative_features:
    confusion_matrix = pd.crosstab(df[col], df["isFraud"])
    cramers_v_values = cramers_v(confusion_matrix)
    print(f"{col} : ", cramers_v_values)

"""Analyse plus détaillée"""
# Relation Variables Continues / Variables Continues
plt.figure(figsize=(12, 8))
sns.heatmap(df[important_num_features].corr(), cbar=True)
scaled_numerical_df = pd.DataFrame(StandardScaler().fit_transform(df[important_num_features]), columns=df[important_num_features].columns)
scaled_numerical_df = scaled_numerical_df.dropna(axis=0)
vif_data = pd.DataFrame()
vif_data["features"] = scaled_numerical_df.columns
vif_data["vif"] = [variance_inflation_factor(scaled_numerical_df.values, i) for i in range(scaled_numerical_df.shape[1])]
print(vif_data)

# Relation Variables Qualitatives / Variables Continues
def cramers_v(chi2, n, k):
    """
    Calcule la valeur de Cramér's V à partir du chi2, du nombre total d'observations et des dimensions de la table de contingence
    """
    return np.sqrt(chi2 / (n * (min(k) - 1)))
def cramers_v_matrix(df, qualitative_vars):
    v_matrix = pd.DataFrame(index=qualitative_vars, columns=qualitative_vars)
    
    for var1 in qualitative_vars:
        for var2 in qualitative_vars:
            if var1 != var2:
                contingency_table = pd.crosstab(df[var1], df[var2])
                chi2, p, dof, expected = stats.chi2_contingency(contingency_table)
                n = contingency_table.sum().sum()
                k = contingency_table.shape
                v_matrix.loc[var1, var2] = cramers_v(chi2, n, k)
            else:
                v_matrix.loc[var1, var2] = 1  # Cramér's V pour une variable avec elle-même est 1
    
    return v_matrix.astype(float)

matrix = cramers_v_matrix(df, important_cat_features)

plt.figure(figsize=(12,8))
sns.heatmap(matrix, annot=True, cmap='coolwarm', center=0, vmin=0, vmax=1)
plt.title('Matrice de Cramér\'s V')

# NaN anlyse
important_features = important_cat_features + important_num_features
msno.matrix(df[important_features])

# Outliers
print("Début de la détection d'anomalie.")
df_clean = df.drop("isFraud", axis=1).select_dtypes(exclude="object").dropna(axis=0)
ID = df_clean["indice"]
df_clean = df_clean.drop("indice", axis=1)

df_scaled = StandardScaler().fit_transform(df_clean)
model = IsolationForest(random_state=0, contamination=0.02)
model.fit(df_scaled)
outliers = model.predict(df_scaled) == -1
print(f"Nombre d'outlies détectés : ", sum(outliers))

anomaly_score = model.decision_function(df_scaled)

plt.figure(figsize=(12,8))
plt.hist(anomaly_score, bins=50)
plt.axvline(x=-0.5, color="red", linestyle="--", label="seuil = -0.5")
plt.title("Distribution des scores d'anomalies.")
plt.xlabel("Seuil d'anomalie")
plt.ylabel("Nombre de points")
plt.legend()
outliers_indices = [i for i, score in enumerate(anomaly_score) if score < -0.1]
outliers_transaction_id = ID.iloc[outliers_indices]
print("indice des outliers < -0.5 : \n", outliers_transaction_id)

# Normality
important_continuous_features = [col for col in important_num_features if df[col].nunique() > 50]
col_to_remove = ["C1", "C2", "C5", "C6", "C9", "C11", "C13", "C14", "D1", "D2", "D11", "dist1"]
important_continuous_features = [col for col in important_continuous_features if col not in col_to_remove]

print(important_continuous_features)
def math_transform(col): 
    df_transform = pd.DataFrame()
    df_transform[col] = df[col].copy()
    df_transform = df_transform.dropna(axis=0)
    #df_transform[col] = df_transform[col].replace(0, 1)

    try:
        df_transform[f"{col}_log"] = np.log(df_transform[col])
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
        stats.probplot(df_transform[col], plot=plt)
        anderson = stats.anderson(df_transform[col], dist="norm")
        stat, p_value = stats.normaltest(df_transform[col])
        print(f"{col} : ", anderson.statistic)
        plt.title(f'{col} | Anderson : {anderson.statistic:.3f} : Normal : {anderson.statistic > anderson.critical_values[2]} | Agostino-Pearson : {p_value:.3f} : Normal : {p_value > 0.05}', fontsize=8)

for col in important_continuous_features:
    math_transform(col)

"""for col in important_continuous_features:
    plt.figure()
    sns.distplot(df[col], fit=norm)
    plt.title(f'{col}')
    plt.figure()
    probplot(df[col], plot=plt)
    plt.title(f'{col}')"""

plt.show()
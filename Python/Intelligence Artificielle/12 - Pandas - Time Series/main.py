"""
L'indexing, le slicing, le masking etc sont possible sur des dates.

Pandas s'adapte à beaucoup de format de date, sinon on peut utiliser la fonction :
pd.to_datetime('2019/03/20')
Pandas peut aussi mesurer le temps en semaine, jour, jusqu'aux nanosecondes

pd.resample() : regroupe les données selon une fréquence temporelle, pour calculer des statistiques :
Y : Year
M : Month
W : Week
D : Day
h : Hour
m : Minute
s : second
ms : millisecond
us : microsecond
ns : nanosecond
pd.resample(2W) : toutes les 2 semaines 

Moving Average : statistique sur une fenêtre de valeur, au lieu de toutes les valeurs
Exponantial Weighted Average : les valeurs perdent de l'importance avec le temps

pd.merge(data1, data2, on='column', how='inner') : fusionne 2 datasets dans la colonne 'column' de manière 'inner'
inner : assemble les dataframes uniquement sur les indexes en commun
outer : assemble entièrement les dataframes
left : assemble avec les indexes en commun et tout le dataframe gauche
right : assemble avec les indexes en commun et tout le dataframe droite

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
import seaborn as sns # permet d'afficher des corrélations dans un graphique

bitcoin = pd.read_csv("BTC-EUR.csv", index_col='Date', parse_dates=True) 
# index_col['Date'] : remplace la colonne d'index du dataframe, par la colonne 'Date'
# parse_dates=True : indique à Pandas que cette colonne d'index doit être interprété comme une date

m = bitcoin['Close'].resample('W').agg(['mean', 'std', 'min', 'max']) # 'agg' permet de regrouper plusie urs statistiques dans un seul tableau

plt.figure(figsize=(12,8))
plt.subplot(2,1,1)
m['mean']['2019'].plot(label='moyenne par semaine') # affiche la moyenne par semaine en 2019
plt.fill_between(m.index, m['max'], m['min'], alpha=0.2, label='min-max par semaine') # fill_between créer une zone, ici d'incertitude entre le minimum et le maximum
plt.legend()

plt.subplot(2, 1, 2)
bitcoin.loc["2019-09", "Close"].plot()
bitcoin.loc["2019-09", "Close"].rolling(window=7).mean().plot(label="Moving Average Non-Center", lw=3, ls=":", alpha=0.8) # calcule la moving average dans une fenêtre de 7 jours
bitcoin.loc["2019-09", "Close"].rolling(window=7, center=True).mean().plot(label="Moving Average Center", lw=3, ls=":", alpha=0.8) # calcule la moving average dans une fenêtre de 7 jours
# center=True : place la moving average au centre de chaque fenêtre

for i in np.arange(0.2, 1, 0.2): # créer un tableau ndarray, puis itère dedans, 'i' entre 0.2 et 1 en faisant des pas de 0.2
    bitcoin.loc["2019-09", "Close"].ewm(alpha=i).mean().plot(label=f"EWM {i}", ls="--", alpha=0.8) # calcule la Exp Weighted Average 'ewm()'
    # alpha=0.5 : facteur de lissage à 'i'
plt.legend()
plt.show()

ethereum = pd.read_csv("ETH-EUR.csv", index_col="Date", parse_dates=True)

btc_eth = pd.merge(bitcoin, ethereum, on='Date', how='inner', suffixes=('_btc', '_eth')) # fusionne les datasets 'bitoin' et 'ethereum' selon la colonne 'Date'
# suffixes=('_btc', '_eth') : remplace les suffixes '_x' et '_y' par les suivants dans le nouveau dataset

btc_eth[['Close_btc', 'Close_eth']].plot(subplots=True, figsize=(12,8)) # créer 2 subplots, un pour 'Close_btc' et un pour 'Close_eth'
plt.show()

correlations = btc_eth[['Close_btc', 'Close_eth']].corr() # renvoie une matrice de corrélation entre 'Close_btc' et 'Close_eth'
sns.heatmap(correlations) # affiche la corrélation
plt.show()


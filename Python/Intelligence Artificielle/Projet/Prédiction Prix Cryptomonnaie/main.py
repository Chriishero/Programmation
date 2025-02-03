
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.pipeline import make_pipeline
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures, RobustScaler, MinMaxScaler, OrdinalEncoder, OneHotEncoder
from sklearn.model_selection import train_test_split, GridSearchCV

crypto = pd.read_csv("sol-usd-max.csv", index_col="snapped_at", parse_dates=True)
crypto.dropna(axis=0, inplace=True)
print(crypto.head())
crypto["date"] = crypto.index
crypto["date"] = crypto["date"].astype('category').cat.codes

y = crypto["price"]
#X = crypto.drop(["price"], axis=1)
X = crypto["date"].values.reshape(-1, 1) # s'assure que le tableau à 2 dimensions

print(X.shape, y.shape)

print("divisé")
X_train, X_test, y_train, y_test = train_test_split(X, y)
model = make_pipeline(PolynomialFeatures(), RobustScaler(), LinearRegression())

params = {
    #'C':np.arange(1, 100)
    "polynomialfeatures__degree":np.arange(2,50)
}

grid = GridSearchCV(model, param_grid=params, cv=5)
print("création grid")
grid.fit(X_train, y_train)
print("grid fit")
print("Meilleur paramètres : ", grid.best_params_)
print("Meilleur modèle : ", grid.best_estimator_)
print("Score : ", grid.score(X_test, y_test))

linear_model = grid.best_estimator_.named_steps['linearregression'] # Cela permet d'accéder à l'étape LinearRegression du pipeline.
coefs = linear_model.coef_ # Récupère les coefficients de la régression linéaire après transformation polynomiale.
intercept = linear_model.intercept_ # Récupère l'interception (biais) du modèle.
# Récupérer le degré du polynôme pour interpréter les coefficients
degree = grid.best_estimator_.named_steps['polynomialfeatures'].degree

# Afficher la fonction polynomiale sous forme lisible
equation = f"y = {intercept:.4f} "
for i in range(1, degree + 1):
    equation += f"+ ({coefs[i]:.4f})x^{i} "

print("La fonction de régression polynomiale est :")
print(equation)

plt.figure(figsize=(12,8))
plt.scatter(crypto.index, y, label='real', alpha=0.8)
plt.plot(crypto.index, grid.predict(X), c='r', label='pred')
plt.show()
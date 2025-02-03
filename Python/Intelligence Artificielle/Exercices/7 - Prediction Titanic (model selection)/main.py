
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split, GridSearchCV, learning_curve
from sklearn.metrics import confusion_matrix

titanic = sns.load_dataset("titanic")
titanic = titanic[["survived", 'pclass', 'age', 'sex']]
titanic.dropna(axis=0, inplace=True)
titanic['sex'].replace(['male', 'female'], [0, 1], inplace=True)

y = titanic['survived']
X = titanic.drop('survived', axis=1)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=1)
model = KNeighborsClassifier()

param_grid = {"n_neighbors": np.arange(1, 50), "metric": ["euclidean", 'manhattan', "canberra"], "weights": ["uniform", "distance"]}
grid = GridSearchCV(model, param_grid=param_grid, cv=5)
grid.fit(X_train, y_train)

print("Meilleur score : ", grid.best_score_)
print("Meilleurs paramètres : ", grid.best_params_)

model = grid.best_estimator_
print("Score test : ", model.score(X_test, y_test))

print(confusion_matrix(y_test, model.predict(X_test)))

N, train_score, val_score = learning_curve(model, X_train, y_train, train_sizes=np.linspace(0.2, 1.0, 5), cv=5)

plt.plot(N, train_score.mean(axis=1), label='train')
plt.plot(N, val_score.mean(axis=1), label='validation')
plt.xlabel("train_sizes")
plt.legend()
plt.show()

import matplotlib.pyplot as plt
from sklearn.datasets import make_classification, make_regression
from sklearn.metrics import accuracy_score, r2_score
from sklearn.model_selection import train_test_split
from rappel import *

type = "classif"
model = LogisticRegression()

plt.figure()
if type == "regression":
    X, y = make_regression(n_samples=500, n_features=10, noise=10, random_state=0)
    y = y.reshape(-1, 1) # sauf pour le XGBoostRegressor
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, random_state=0)

    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    plt.scatter(y_test, y_pred)
    plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], color='r')
    plt.title(f'{r2_score(y_test, y_pred)}')
elif type == "classif":
    X, y = make_classification(n_samples=500, n_features=10, n_informative=8, n_classes=2, random_state=0)
    #y = y * 2 - 1 # SVM
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, random_state=0)

    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    plt.scatter(X_test[:, 0], y_test)
    plt.plot(X_test[:, 0], y_pred, color='r')
    plt.title(f'{accuracy_score(y_test, y_pred)}')
plt.show()


import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVR
from sklearn.metrics import make_scorer # permet de créer ses propres métriques de validation
from sklearn.model_selection import GridSearchCV

m = 200
X = np.linspace(0, 3, m).reshape((m, 1))
y = 2 + X**2.1 + np.random.randn(m, 1)
y = y.ravel()

def custom_metric(y, y_pred):
    return np.sqrt(1/y.size * (np.sum((y-y_pred)**2)))
    #return np.sqrt(np.mean((y-y_pred)**2))

custom_score = make_scorer(custom_metric, greater_is_better=False)

model = SVR()
params = {"gamma": np.arange(0.1, 1, 0.05)}
grid = GridSearchCV(model, param_grid=params, cv=3, scoring=custom_score)
grid.fit(X, y)
best_model = grid.best_estimator_
y_pred = best_model.predict(X)
print("Score : ", custom_metric(y, y_pred))

plt.figure(figsize=(12,8))
plt.scatter(X, y)
plt.plot(X, y_pred, c='r', lw=3)
plt.show()
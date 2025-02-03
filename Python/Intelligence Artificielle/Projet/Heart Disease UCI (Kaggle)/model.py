
import numpy as np 
import matplotlib.pyplot as plt 
import pandas as pd 
from sklearn.ensemble import AdaBoostClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import f1_score, confusion_matrix, classification_report
from sklearn.model_selection import learning_curve

X_train = pd.read_csv("preprocessing/X_train.csv")
y_train = pd.read_csv("preprocessing/y_train.csv")
X_test = pd.read_csv("preprocessing/X_test.csv")
y_test = pd.read_csv("preprocessing/y_test.csv")

y_train = y_train.values.ravel()
y_test = y_test.values.ravel()

model = AdaBoostClassifier(random_state=0, n_estimators=100, learning_rate=0.04,
                            estimator=DecisionTreeClassifier(random_state=0, criterion='gini', splitter='random', max_depth=3,
                            min_samples_split=30, min_samples_leaf=1)) # bref 0.861

def evaluation(model):
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    print(confusion_matrix(y_test, y_pred))
    print(classification_report(y_test, y_pred))

    N, train_score, val_score = learning_curve(model, X_train, y_train, cv=4, scoring='f1', train_sizes=np.linspace(0.1, 1, 10))

    plt.figure(figsize=(12,8))
    plt.plot(N, train_score.mean(axis=1), label="Train Score")
    plt.plot(N, val_score.mean(axis=1), label="Validation Score")
    plt.title(f"F1-Score : {f1_score(y_test, y_pred)}")
    plt.legend()
    
evaluation(model)

plt.show()

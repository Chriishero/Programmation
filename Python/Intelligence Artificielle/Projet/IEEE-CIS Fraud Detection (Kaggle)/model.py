"""
AIDE À L'ANALYSE : 
https://www.kaggle.com/code/pmarcelino/comprehensive-data-exploration-with-python/notebook
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.pipeline import make_pipeline
from sklearn.model_selection import learning_curve, GridSearchCV, RandomizedSearchCV
from sklearn.metrics import *
from sklearn.preprocessing import PolynomialFeatures
from sklearn.feature_selection import SelectKBest, SelectFromModel, f_regression, mutual_info_regression
from sklearn.linear_model import LinearRegression
from sklearn.svm import SVR
from sklearn.ensemble import GradientBoostingRegressor, RandomForestRegressor, BaggingRegressor, VotingRegressor, StackingRegressor
from sklearn.tree import DecisionTreeRegressor, ExtraTreeRegressor
from lightgbm import LGBMClassifier
from xgboost import XGBClassifier
from catboost import CatBoostClassifier

X_train = pd.read_csv("set/X_train.csv", index_col=0)
y_train = pd.read_csv("set/y_train.csv", index_col=0)
X_test = pd.read_csv("set/X_test.csv", index_col=0)
y_test = pd.read_csv("set/y_test.csv", index_col=0)

y_train = y_train.values.ravel()
y_test = y_test.values.ravel()

model = make_pipeline(
    XGBClassifier( # 0.8711 (1.0 - 0.85) 500 et 9 et 0.25 || 0.8247 (0.90 - 0.82) 175 et 4 et 0.3
        # Paramètres principaux
        booster="gbtree",               # Type de booster : 'gbtree', 'gblinear', ou 'dart'
        random_state=0,                 # Aléatoire pour reproductibilité
        verbosity=1,                    # Niveau de verbosité : 0 (silencieux) à 3 (debug)
        validate_parameters=True,       # Valide les paramètres non reconnus
        disable_default_eval_metric=False, # Active la métrique par défaut

        # Paramètres liés aux arbres
        n_estimators=175,               # Nombre d'arbres (boosting rounds) et OVERFITTING
        max_depth=4,                    # Profondeur maximale des arbres et OVERFITTING
        max_leaves=0,                   # Nombre maximal de feuilles (0 = illimité)
        max_bin=256,                    # Nombre maximum de bins pour l'algorithme histogram-based
        grow_policy="depthwise",        # Politique de croissance des arbres ('depthwise' ou 'lossguide')

        # Paramètres de boosting
        learning_rate=0.3,              # Taux d'apprentissage (alias eta) et OVERFITTING
        tree_method="auto",             # Méthode d'arbre (auto par défaut)
        subsample=1.0,                  # Fraction des échantillons pour chaque arbre
        colsample_bytree=1.0,           # Fraction des colonnes utilisées pour construire chaque arbre
        colsample_bylevel=1.0,          # Fraction des colonnes par niveau
        colsample_bynode=1.0,           # Fraction des colonnes par split
        sampling_method="uniform",      # Méthode d'échantillonnage (uniquement pour GPU)

        # Régularisation
        gamma=0,                        # Perte minimum pour créer un split (alias min_split_loss)
        min_child_weight=1,             # Poids minimum pour créer une feuille
        reg_alpha=0,                    # Régularisation L1
        reg_lambda=1,                   # Régularisation L2 ET OVERFITTING
        max_delta_step=10,               # Étape maximale pour ajuster les poids

        # Gestion des classes déséquilibrées
        scale_pos_weight=1,             # Poids pour équilibrer les classes positives et négatives

        # Performance et matériel
        n_jobs=-1,                       # Nombre de threads parallèles
        device="cpu",                   # Matériel pour l'exécution ('cpu', 'cuda', ou 'gpu')

        # Objectif et métriques
        objective="binary:logistic",    # Objectif de la tâche (binaire)
        eval_metric=None,               # Métrique d'évaluation (par défaut dépend de l'objectif)

        # Gestion des valeurs manquantes
        missing=np.nan,                   # Valeurs manquantes (par défaut np.nan)

        # Options avancées
        monotone_constraints=None,      # Contraintes de monotonie (aucune par défaut)
        interaction_constraints=None,   # Contraintes d'interaction (aucune par défaut)
        importance_type="gain",         # Type d'importance des caractéristiques
        enable_categorical=False,       # Support des colonnes catégoriques (doit être activé explicitement)
        max_cat_to_onehot=None,         # Seuil pour utiliser le one-hot encoding (catégories)
        max_cat_threshold=None,         # Nombre max de catégories par split
        multi_strategy=None,            # Stratégie pour multi-target
        early_stopping_rounds=None,     # Arrêt anticipé si aucune amélioration
        callbacks=None                  # Liste de callbacks (aucune par défaut)
    )
)
model = make_pipeline(LGBMClassifier( # 0.8208 (0.88 - 0.82)
    # Paramètres principaux
    boosting_type="gbdt",            # Type de boosting : 'gbdt' (classique), 'dart', 'rf' (random forest), 'goss'
    random_state=0,                   # Aléatoire pour reproductibilité
    verbosity=-1,                      # Niveau de verbosité : -1 (silencieux), 0 (erreurs), 1 (warnings), 2 (info)
    force_col_wise=False,              # Forcer le stockage des features en colonnes (optimisation mémoire)
    force_row_wise=False,              # Forcer le stockage des features en lignes

    # Paramètres liés aux arbres
    n_estimators=250,                  # Nombre total d'arbres (nombre de boosting rounds)
    max_depth=3,                      # Profondeur maximale des arbres (-1 = illimité)
    num_leaves=25,                     # Nombre maximal de feuilles par arbre (impacte la complexité et l'overfitting)
    max_bin=200,                       # Nombre maximum de bins pour discrétiser les valeurs continues
    min_data_in_leaf=20,               # Nombre minimum d'échantillons par feuille
    min_sum_hessian_in_leaf=1e-3,      # Somme minimale des hessians (poids) dans une feuille
    extra_trees=False,                 # Utiliser Extra Trees (plus de variance, moins de biais)
    feature_fraction_bynode=1.0,       # Fraction des features utilisées pour un split

    # Paramètres de boosting
    learning_rate=0.3,                 # Taux d'apprentissage (alias shrinkage)
    boosting="gbdt",                   # Type de boosting ('gbdt', 'dart', 'goss', 'rf')
    bagging_fraction=1.0,              # Fraction des échantillons pour chaque itération (a.k.a. subsample)
    bagging_freq=0,                    # Fréquence du bagging (0 = désactivé)
    bagging_seed=0,                    # Seed pour le bagging
    feature_fraction=1.0,              # Fraction des features utilisées par arbre
    feature_fraction_seed=0,           # Seed pour le sous-échantillonnage des features

    # Régularisation et overfitting
    lambda_l1=1.0,                     # Régularisation L1 (alias reg_alpha)
    lambda_l2=0.0,                     # Régularisation L2 (alias reg_lambda)
    min_gain_to_split=0.0,             # Gain minimal pour créer un split (alias gamma dans XGBoost)
    max_delta_step=0.0,                # Pas maximal pour ajuster les poids

    # Gestion des classes déséquilibrées
    scale_pos_weight=1.0,              # Poids des classes pour gérer les classes déséquilibrées
    is_unbalance=False,                # Active automatiquement le rééquilibrage des classes si True
    class_weight={0: 1, 1: 1},                 # Permet d’attribuer des poids spécifiques à chaque classe

    # Performance et matériel
    n_jobs=-1,                         # Nombre de threads parallèles (-1 = utiliser tous les cœurs)
    device="cpu",                       # Exécution sur CPU ou GPU
    gpu_use_dp=False,                   # Activer la double précision sur GPU
    gpu_platform_id=-1,                 # ID de la plateforme GPU
    gpu_device_id=-1,                   # ID du GPU utilisé

    # Objectif et métriques
    objective="binary",                 # Objectif d'apprentissage ('binary', 'multiclass', 'regression', etc.)
    metric="binary_logloss",            # Métrique d'évaluation (aucune par défaut pour regression)
    eval_at=None,                       # Liste des itérations à évaluer

    # Gestion des valeurs manquantes
    missing=np.nan,                       # Valeurs manquantes (None, np.nan, ou autre valeur)

    # Options avancées
    monotone_constraints=None,          # Contraintes de monotonie sur certaines features
    interaction_constraints=None,       # Contraintes d'interaction entre variables
    importance_type="split",            # Type d'importance des features ('split' ou 'gain')
    cat_l2=10.0,                        # Régularisation L2 pour les features catégorielles
    cat_smooth=10.0,                    # Lissage pour les variables catégorielles
    max_cat_threshold=32,               # Nombre max de catégories par split
    max_cat_to_onehot=4,                # Seuil pour encoder en one-hot les variables catégorielles

    # Gestion avancée du boosting
    early_stopping_rounds=None,         # Nombre d'itérations sans amélioration avant d'arrêter
    callbacks=None                      # Liste de callbacks pour customiser l'entraînement
))

def inverse_transform(X_test, y_test, y_pred):
    print("début inverse transform")   

    if "TransactionDT" in X_test.columns:
        X_test["TransactionDT"] = X_test["TransactionDT"]**2

    cbrt_col = ["C4", "C7", "C8", "C10", "C12", "D3", "D5", "D10"]
    for col in cbrt_col:
        if col in X_test.columns:
            X_test[col] = X_test[col]**3

    return X_test, y_test, y_pred

def evaluation(model):
    print("début évaluation")
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    X_test_inv, y_test_inv, y_pred_inv = inverse_transform(X_test, y_test, y_pred)

    print(confusion_matrix(y_test_inv, y_pred_inv))
    print(classification_report(y_test_inv, y_pred_inv))
    print("F1 Score : ", f1_score(y_test_inv, y_pred_inv, average='binary'))

    print("début learning curve")
    N, train_score, val_score = learning_curve(model, X_train, y_train, cv=4, train_sizes=np.linspace(0.1, 1, 10))

    print("début graph")
    plt.figure(figsize=(10, 6))
    plt.plot(N, train_score.mean(axis=1), label="Train Score")
    plt.plot(N, val_score.mean(axis=1), label="Validation Score")
    plt.title(f"F1 Score : {f1_score(y_test_inv, y_pred_inv, average='binary')}")
    plt.legend()

evaluation(model)

plt.show()

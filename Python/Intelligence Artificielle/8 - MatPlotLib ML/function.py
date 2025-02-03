"""
------Tracer des Graphiques en utilisant les fonctions------
Pour tracer y en fonction de x, x et y doivent avoir les mêmes dimensions

plt.figure(figsize=(x, y)) : créer une figure vide, de dimension (x,y), c'est la feuille de travail
plt.scatter(x, y, label=, lw=, ls=, c=) : trace un nuage de point
plt.plot(x, y, label=, lw=, ls=, c=) : trace une courbe
label : nom de la courbe
lw : épaisseur du tratit
ls : style du trait
c : couleur du trait

Les courbes sont cumulable sur la figure.
plt.title("text") : ajoute un titre à la figure
plt.xlabel("text") : nom pour l'axe 'x'
plt.ylabel("text") ; nom pour l'axe 'y'
plt.legend() : affiche une légende pour chaque courbe, le paramètre 'label=' doit être initialisé pour les courbes

plt.savefig("fig.png") : sauvegarde la figure

plt.subplot(2, 1, 1) : créer un sous graphique de 2 lignes, 1 colonnes et de position 1
plt.subplot(2, 1, 2)
"""

import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0,2,10) # tableau de 10 points allant de 0 à 2
y = x**2

plt.figure() # créer une figure vide
plt.subplot(2,1,1) # créer un premier graphique sur la figure
plt.plot(x,y, lw=3, ls="--", label="quadratique") # trace la courbe de 'y' en fonction de 'x', d'épaisseur '3', avec un style de '-'
plt.scatter(x,y, c="red") # trace un nuage de point rouge de 'y' en fonction de 'x'
plt.title("Graphique 1")
plt.legend() # affiche la légendes (label) 'quadratique'

plt.subplot(2,1,2) # créer un deuxième graphique sur la figure
plt.plot(x, x**3, label="cubique")
plt.legend() # affiche la légendes (label) 'cubique'

plt.show() # affiche le graphique
plt.savefig("matplotlib.png")

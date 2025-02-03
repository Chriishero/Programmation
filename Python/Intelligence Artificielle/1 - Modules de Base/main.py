"""
===============
MATH
================
"""
import math

print(math.cos(2*math.pi)) # renvoie le cos de 2* pi
print(math.exp(5)) # exponentielle de 5

"""
===============
STATISTICS
==============
"""
import statistics

liste = [1, 5, 2, 6 ,9 ,20, 52]
print(statistics.mean(liste)) # renvoie la moyenne des valeurs la liste
print(statistics.variance(liste)) # renvoie la variance

"""
==============
RANDOM
==============
"""
import random

random.seed(0) # '0' définie une graine de répétabilité, l'élément généré sera toujours le même

print(random.choice(liste)) # choisi un élément aléatoire d'une liste
print(random.choice(["Jean", "Justine", "Bryan", "Ivan"]))

print(random.random()) # float
print(random.randint(5, 10)) # int entre 5 et 10
print(random.randrange(100)) # int 0 et 100

print(random.sample(range(100), 10)) # renvoie une liste de 10 éléments dans une fourchette de 0 à 100

random.shuffle(liste) # mélange aléatoirement les éléments d'une liste

"""
==========
OS
=========
"""
import os

print(os.getcwd()) # renvoie le répertoire actuel

"""
=============
GLOB
=============
"""
import glob

print(glob.glob("*")) # renvoie tous (*) les fichiers et dossiers contenue dans le répertoire de travail actuel
print(glob.glob("*.txt")) # tous les fichiers de type 'txt'
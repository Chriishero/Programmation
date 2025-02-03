"""
Les dictionnaires peuvent contenir n'importe quel objet, même un tuple.

Création de dictionnaire : dict = {} : vide
                           dict = {key:value, key2:value2}

dict[key]         : accède à la valeur de la 'key'
dict[key] = value : ajoute/modifie une 'value' à partir de sa 'key'
dict2 = dict1        : 'dict2' fait référence à 'dict1'
dict2 = dict1.copy() : 'dict2' fait une copie de 'dict1'

Suppresion : dict.pop(key)
             del dict[key]

dict.__contains__(key) : vérifie si 'dict' contient la clé 'key'
dict.keys()   : renvoie les clé (peu être utilisé dans une boucle for)
dict.values() : renvoie les valeurs (idem)
dict.items()  : renvoie les 2 (idem avec un tuple comme : key, value)
dict.fromkeys(keyList, defaultValue) : créer un dictionnaire avec comme clé, les valeurs de la 'keyList' et en valeur par défaut pour chaque 'defaultValue' (optionnel)

Dict comprehension : 

names = ["Chris", "Ivan", "Justine", "Bryan"]
dico = {k:v for k, v in enumerate(names)} : pour tous les éléments de la liste 'names', crée un couple de chiffres et de ses éléments

age = [25, 55, 36, 25]
dico2 = {names:age for names, age in zip(names, age) if age > 30} : idem, en associant les listes 'names' et 'age', mais sous une condition

L'utilité des 'comprehension', c'est que le code est plus court et le processus de création dans la mémoire se fait plus rapidement.
"""

dict = {1:2451, "Prénom":"Chris"}
dict["Chien"] = "Louki"

print(dict)
deleteValue = dict.pop(1) # il est possible de stocker la valeur supprimé
print(dict)

print(dict.__contains__("Prénom"))

if "Prénom" in dict:
    print("'dict' contient la clé 'Prénom'")

for (k,v) in dict.items():
    print(f"{k} : {v}")

def weirdFunction(**params): # '**' permet un nombre infinie de paramètres obligatoirement nommés
    print(params) # renvoie un dictionnaire de clé : nom paramètre ; valeur : paramètre

weirdFunction(a="oui", b="non") # params = {"a":"oui", "b":"non"}


"""
Les tuples sont immuables, on ne peut ni supprimer, ni ajouter des éléments.

Raisons d'utiliser les tuples : affectation multiple
                                retour multiple de fonction

Création de tuple : tuple = ()       : vide
                    tuple = (17,)    : une seule valeur
                    tuple = 17,      : idem
                    tuple (17, 0, 5) : plusieurs valeurs

tuple[X] : accède à l'élément à l'indice 'X'

Tuple comprehension : 

tuple1 = tuple((i for i in range(10))) : instancie 0 à 9 dans une générateur, puis convertie le générateur en tuple avec 'tuple()'

L'utilité des 'comprehension', c'est que le code est plus court et le processus de création dans la mémoire se fait plus rapidement.
"""

myTuple = (45,)
print(myTuple[0])

(n1, n2) = (14, 46) # affectation multiple, en utlisant le principle des tuples
print(f"{n1} ; {n2}")

n1 = 5 # on peut modifier les valeurs si il s'agit d'une affectation multiple
print(f"{n1} ; {n2}")


def get_player_positon():
    posX = 562
    posY = 25

    return (posX, posY) # retour multiple grâce au tuple

coordX = 0
coordY = 0

print(f"Position du joueur : ({coordX}/{coordY})")
(coordX, coordY) = get_player_positon() # affectation multiple du retour multiple
print(f"Position du joueur : ({coordX}/{coordY})")
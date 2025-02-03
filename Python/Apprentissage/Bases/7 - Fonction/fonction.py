"""
def function(*params) : '*' permet un nombre infinie de paramètres
def function(**params) : '**' permet un nombre infinie de paramètres nommés
"""

def show_inventory(*items):
    for item in items:
        print(item)

show_inventory("épée")
show_inventory("épée", "arc", "potion de mana")


def next_year():
    global year
    print("Fin de l'année", year)
    year += 1
    print("Début de l'année", year)


year = 2018
next_year()
print("//////////////////////////////////////////////////////////////////////////////////////////////")

def addition():
    return 5 + 5


def multiply():
    return 5 * 8


def get_message():
    return "Le resultat du calcul est"


print(get_message(), addition())
print(get_message(), multiply())
print("/////////////////////////////////////////////////////////////////////////////////////////////////////////")

def addition1(n):
    return 5 + n


print(get_message(), addition1(5))
print(get_message(), addition1(4))
print(get_message(), addition1(9))
print("///////////////////////////////////////////////////////////////////////////////////////////")

# creer une fonction max() qui va renvoyer le resultat le plus haut entre 2 valeurs
def max(a, b):
    if a > b:
        return a

    elif b > a:
        return b

first_value = int(input("Entrer une premiere valeur "))
second_value = int(input("Entrer une seconde valeur "))
max_value = max(first_value, second_value)
print("La valeur max est", max_value)

print("///////////////////////////////////////////////////////////////////////////////////////////////////////////")

def add(a):
    a += 1
    print(a)

    if a < 10:
        add(a)


add(2)

"""
liste = list() : instanciation d'une liste
liste = []
 
liste = [0] * 10 : instancie la liste avec dix 0
liste = range(20) : instancie des chiffres de 0 à 19

liste[X]   : renvoie l'élément à l'indice X
liste[-X]  : renvoie le Xème élement en partant de la fin
liste[:]   : renvoie tous les éléments
liste[:X]  : renvoie les X premiers élements
liste[X:]  : renvoie les X derniers éléments
liste[X:Y] : renvoie de l'élément d'indice X à l'élément d'indice Y (exclus)

liste.append(e) : insert l'élément 'e' à la fin de la liste
liste.insert(X, e) : insert l'élément 'e' à l'indice X

liste.remove(e) : supprime l'élément 'e'
del liste[X] : supprime l'élément à l'indice X
liste.clear() : supprime tous les élément de la liste

liste.index(e) : renvoie l'indice de l'élément 'e'
liste.sort()   : trie une liste avec des éléments de même type
liste.reverse() : inverse l'ordre des éléments d'une liste de même type

liste.count(e) : compte le nombre d'occurence de l'élément 'e'

string = " ".join(liste) : joins tous les éléments de la liste par le caractère " " pour créer une string

liste2 = liste1 : 'liste2' est une référence à 'liste1'
liste1.extend(liste2) : étend 'liste1' avec le contenue de 'liste2'
liste1 += liste2

List comprehension : 

liste = [i**2 for in in range(10)] : instancie tous les carré de 0 à 9 dans la liste
liste1 = [[i for i in range(3)] for j in range(3)] : instancie 3 listes qui contiennent 0, 1 et 2 dans la liste 'liste1' 

L'utilité des 'comprehension', c'est que le code est plus court et le processus de création dans la mémoire se fait plus rapidement.

"""
import copy

liste = ["Arc", "épée", "Lance", "Bouclier"]

for indice, value in enumerate(liste): # énumère les indices et valeurs de la liste
    print(f"{indice} : {value}")

print(liste[:]) # affiche tous les éléments de la liste
print(liste[:2]) # affiche les 2 premiers élément de la liste
print(liste[2:]) # affiche les 2 derniers élément de la liste
print(liste[-1]) # affiche le premier élément en partant de la fin

if "épée" in liste:
    print("Je possède une épée.")
else:
    print("Je ne possède pas d'épée")

liste[:] = ["Armure"] * len(liste) # remplace tous les élements par 'Armure'
print(liste[:])

liste[0:2] = ["Lance"] # remplace les 2 premiers éléments par une seule fois l'élément 'Lance'
print(liste[:])

del liste[len(liste)-1] # supprime le dernier élément

liste2 = copy.deepcopy(liste) # copie 'liste' dans 'liste2' au lieu d'en faire une référence à 'liste'
print(f"Liste : {liste[:]}")
print(f"Liste2 : {liste2[:]}")

liste2.append("Bouclier")

print(f"Liste : {liste[:]}")
print(f"Liste2 : {liste2[:]}")
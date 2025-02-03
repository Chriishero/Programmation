"""
Gérer les exceptions : try/except (+ else, finally)

Types d'exceptions  : ValueError
					  NameError
					  TypeError
					  ZeroDivisionError
					  OSError
					  AssertionError
"""

user_age = input("Quel âge as-tu ?")

try: # Essaye cet instruction
	user_age = int(user_age)

except: # Si il y a une exception n'import laquel
	print("L'âge indiquer est incorrect")

else: # Sinon (si il n'y a pas d'exception) tu affiches ça
	print("Tu as {} ans".format(user_age))

finally: # Tout ce qui se passe dans ce bloque sera dans tout les cas executé
	print("FIN DU PROGRAMME...")

#/////////////////////////////////////////////////////////////////////////////////////

nombre1 = 150
nombre2 = input("Choisir le nombre pour diviser 150 : ")

try: # Essaye ces instructions
	nombre2 = int(nombre2)
	print("Résultat = {}".format(nombre1 / nombre2))

except ZeroDivisionError: # Si il y a l'exception "ZeroDivisionError" alors execute le code suivant
	print("Vous ne pouvez pas diviser par zéro.")

except ValueError: # Si il y a l'exception "ValueError" alors execute le code suivant
	print("Vous devez entrer un nombre entier.")

except: # Si c'est un exception différente de "ZeroDivisionError" et "ValueError" alors execute le code suivant
	print("Valeur incorrect.")

else: # Sinon (si il n'y a pas d'exception) tu executes le code suivant
	print("Bravo, tu as noté un nombre valide ! ")

finally: # Tout ce qui se passe dans ce bloque sera dans tout les cas executé
	print("FIN DU PROGRAMME...")

#///////////////////////////////////////////////////////////////////////////////////////

age = input("Quel âge as-tu 2?")
age = int(age)

if age > 25: # Le mot clé raise permet de lever n'importe quelle exception (erreur) et y affecter un message ou une valeur
	raise ZeroDivisionError("Bonjour :)") 

# /////////////////////////////////////////////////////////////////////////////////////////

try:
	age = input("Quel âge as-tu 3?")
	age = int(age)

	assert age > 25 # Je veux que age soit plus grand que 25 sinon je lève l'exception "AssertionError"

except AssertionError:
	print("J'ai attrapé l'exception !")

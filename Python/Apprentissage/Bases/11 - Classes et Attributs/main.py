"""
------------------------------------------------------------
La programmtion orienté-objet (POO) avec le langage Python
------------------------------------------------------------

Classe   : plan de conception, genre (ex : Humain, batiment, joueur...)
Objet    : instance d'une classe (ex : Bob est une instance de la classe humain)
Attribut : variable de classe (ex : prenom, age, taille, sexe)

Les getter et setter ne sont pas nécessaire en python pour accèder à l'attribut d'une classe, contrairement au C++.
"""

class Human:
	"""
	Classe des êtres humains
	"""

	n_human = 0

	def __init__(self, name="Bob", age=1): # Constructeur de la classe (__init__) et l'atribut "self" qui est un attribut qui cible l'objet lui même avec 
										   # les attributs name et age qui ont pour valuer par defaut "Bob" et "1"
		print("Création d'un humain...")
		self.name = name # Création de l'attribut "name" qui a pour valeur le paramètre "name" du constructeur
		self.age = age # Création de l'attribut "age" qui a pour valeur le paramètre "age" du constructeur
		Human.n_human += 1 # on incrémente 1 à l'attribut de classe 'n_human' de la classe 'Human'
		# On utilise 'Human.' au lieu de '.self' car 'n_human' appartient à la classe elle-même, et non à l'objet créé (self)
	

h = Human() # La variable h fait appelle à la classe "Human" sans attribut pour garder les valeur par defaut de "name" et "age"
print("Prenom par defaut des humains -> {}".format(h.name)) # Le .format fait appel à l'attribut "name" qui se trouve dans la classe Human depuis la variable "h"
print("Âge par defaut des humains -> {}".format(h.age))
print(f"Human existant : {Human.n_human}") # Même chose pour 'Human.' au lieu de 'self.'

h1 = Human("Jean", 30) # La variable h1 fait appelle à la classe "Human" et inisialize les attribut "name" et "age" en "Jean" et "30" 
print("Prenom entré de h1 -> {}".format(h1.name))
print("Âge entré de h1 -> {}".format(h1.age))

h1.name = "Thomas" # Initialize une nouvelle valeur à l'attribut "name"
print("Nouveau prenom de h1 -> {}".format(h1.name))
h1.age = 15 # Initialize une nouvelle valeur à l'attribut "age"
print("Nouveau âge de h1 -> {}".format(h1.age))

h2 = Human("Jojo", 40)
print("Prenom entré de h2 -> {}".format(h2.name))
print("Âge entré de h2 -> {}".format(h2.age))

h2.name = "Albert" 
print("Nouveau prenom de h2 -> {}".format(h2.name))
h2.age = 26 
print("Nouveau âge de h2 -> {}".format(h2.age))
print(f"Human existant : {Human.n_human}") 
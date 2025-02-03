"""
Propriété : manière de manipuler/contrôler des attributs 
			principe d'encapsulation !
"""

class Human(object):
	"""docstring for Human"""
	def __init__(self, name, age):
		self.name = name
		self._age = age # L'enderscore (_) est utilisé pour dire que la valeur de cet objet sera modifié/manipulé seulement dans cette classe
		# c'est une aide visuelle

	def _getage(self): # Propriété <getter> ou appelé "accesseurs", get pour récupérer la valeur de l'objet
		try :  
			if self._age <= 1: # Si l'âge est inférieur ou égale à 1 alors ça retourne l'âge + "an" sans s
				return str(self._age) + " an"

			else: # Sinon ça retoune l'âge + "ans" avec s
				return str(self._age) + " ans"

		except AttributeError: # Si il y a un error de type attribut alors 
			print("L'âge n'existe pas !") # Affiche "L'âge n'existe pas !"

	def _setage(self, new_age): # Propriété <setter> ou appelé "mutateurs", set pour changer les valeurs d'un objet
		if new_age < 0: # Si le nouvelle âge est inférieur à 0
			self._age = 0 # Alors self.age sera mis à 0

		else: # Sinon
			self._age = new_age # self.age sera égale au nouveelle âge "new_age"

	def _delage(self): # Fonction qui supprime/detruit l'objet self._age
		del self._age

	# property(<getter>, <setter>, <deleter>, <helper>)
	age = property(_getage, _setage, _delage, "Je suis l'age d'un humain !")


h1 = Human("Jason", 26)
print(f"{h1.name} a {h1.age}.")

h1.age = -5
print(f"{h1.name} a {h1.age}.")

del h1.age # On modifie la valeur de h1 comme "h1.age = 3" mais là ça la supprime
print(f"{h1.name} a {h1.age}.")

help(Human) # Affiche la classe et les methodes en console mais pour l'objet "age" il affiche "Je suis l'age d'un humain !"
help(Human.age) # Affiche seulement la variable de propriété "age"

h1.age = 1
print("{} a {}.".format(h1.name, h1.age))
h1.age = 45
print("{} a {}.".format(h1.name, h1.age))
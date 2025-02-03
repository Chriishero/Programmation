"""
Methode standard  : fonction sur une instance (objet)
Methode de classe : fonction sur une classe
Methode statique  : fonction indépendante mais "lié" à une classe
"""

class Human:
	"""docstring for Human"""

	dwelling_place = "Terre"

	def __init__(self, name, age):
		self.name = name
		self.age = age

	def speak(self, message): # self = Méthode standard
		print("{} a dit : {}".format(self.name, message))

	def planet_change(cls, new_planet): # cls = Méthode de classe 
		Human.dwelling_place = new_planet # Human.dwelling_place sert à recuperer l'attribut de classe "dwelling_place"
		
	planet_change = classmethod(planet_change) # Définit la Méthode de classe "planet_change"

	def definition(): # Ne pas mettre self ou cls = Méthode statique
		print("L'humain est classé comme étant le plus haut être-vivant de la chaîne alimentaire.")

	definition = staticmethod(definition) # Définit la Méthode statique "definition"

h1 = Human("Jason", 26)

h1.speak("Bonjour !") # La classe Human contenue dans la variable h1 utilise la fonction speak en attribuant "Bonjour !" à l'attribut message
h1.speak("Comment allez-vous ?")

print("Planète actuelle : {}".format(Human.dwelling_place))
Human.planet_change("Mars") # Appel la Methode de classe "planet_change" depuis la variable "planet_change"
print("Planète actuelle : {}".format(Human.dwelling_place))

Human.definition() # Utilise la méthode statique "definition"
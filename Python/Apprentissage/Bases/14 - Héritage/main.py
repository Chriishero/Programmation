"""
Fonctions utiles :
	
	isinstance(<objet>, <class>) : vérifie qu'un objet est de la classe renseignée
	issubclass(<class_fille>, <class_mere>) : vérifie qu'une classe est fille d'une autre
"""

# Classe Mère
class Vehicule:
	"""docstring for Vehicule"""
	def __init__(self, name, fuel_quantity):
		self.name = name
		self.fuel_quantity = fuel_quantity

	def move(self):
		print("Le véhicule {} se déplace...".format(self.name))
	
# Classe Fille	
class Voiture(Vehicule): # Entre parenthèse se trouve le nom de la classe mère "Vehicule" pour que la classe fille "Voiture" y récupère tout les arguments et méthodes de celle-ci
	def __init__(self, name, fuel_quantity, power):
		Vehicule.__init__(self, name, fuel_quantity) # Appel le constructeur de la classe mère (Vehicule) avec ses attributs
		self.power = power

	def move(self): # Réécris la méthode "move" déjà existante dans la classe mère
		print("La voiture {} roule...".format(self.name))

# Classe fille
class Avion(Vehicule):
	def __init__(self, name, fuel_quantity, merchandise):
		Vehicule.__init__(self, name, fuel_quantity)
		self.merchandise = merchandise

	def move(self): # Réécris la méthode "move" déjà existante dans la classe mère
		print("Le {} survole les aires !".format(self.name))


voiture1 = Voiture("Toyota Supra", 90, 420) # "voiture1" appelle la classe fille "Voiture" ainsi que ces attributs et ce de la classe "Vehicule" depuis l'argument de la classe "Voiture" 
voiture1.move() # Cherche si la méthode existe dans la classe fille "Voiture" si oui elle l'active sinon elle remonte dans la classe mère pour la trouver
print(voiture1.power, "CH")

av1 = Avion("F22 Raptor", 2400, "Missiles")
av1.move()

if issubclass(Voiture, Vehicule): # Vérifie si la classe fille "Voiture" appartient à la classe mère "Vehicule"
	print("La voiture est un vehicule.")

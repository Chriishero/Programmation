
class Player:
	def __init__(self, pseudo, health, attack):
		self.pseudo = pseudo
		self.health = health
		self.attack = attack
		self.weapon = None
		print("Bienvenue au joueur ", pseudo, " / Points de vie : ", health, " / Attack : ", attack)

	def get_pseudo(self):
		return self.pseudo

	def get_health(self):
		return self.health

	def get_attack_value(self):
		return self.attack

	def damage(self, damage):
		self.health -= damage
		print("Aie... vous venez de subir", damage, "dégats !")

	def attack_player(self, target_player):
		damage = self.attack

		# si le joueur a une arme
		if self.has_weapon():
			# ajoute les dégats de l'arme au point d'attaque du joueur
			damage += self.weapon.get_damage_amount()
			
		target_player.damage(damage)

	# méthode pour changer l'arme du joueur
	def set_weapon(self, weapon):
		self.weapon = weapon

	# méthode pour vérifier si le joueur à une arme
	def has_weapon(self):
		return self.weapon is not None
#coding:utf-8
"""
EXERCICE PYTHON #6
[Révision : gestion d'erreurs, classes et attributs, propriétés, méthodes]

> Vous êtes enseignant en programmation Python et un de vos étudiants vient de vous rendre un devoir. Malheureusement, le programme contient quelques erreurs, à vous de les corriger et permettre l'exécution de ce dernier.

> Le programme doit donner comme résultat l'affichage du fichier "out.txt"

> Le but de cet exercice, en plus de faire réviser les notions citées plus haut, est de vous familiariser avec le débogage d'un code qui n'a pas été fait par vous-même, et prendre l'habitude de lire les messages d'erreur retournés par l'interpréteur et savoir identifier l'origine des bugs dans le code.
"""

#-------------------------------------------------------------------------------------
# CLASSE OBJET POUR JOUEUR
#-------------------------------------------------------------------------------------
class Weapon:
    def __init__(self, name, damages, sell_price):
        self.name = name
        self.damages = damages
        self.sell_price = sell_price

#-------------------------------------------------------------------------------------
# CLASSE JOUEUR
#-------------------------------------------------------------------------------------
class Player:
    def __init__(self, name, level = 1, golds = 5, HP = 100, MP = 100, EXP = 0, weapon = Weapon("Épée en bois", 32, 1)):
        self._name = name
        self.level = level
        self.golds = golds
        self.HP = HP
        self.maxHP = HP
        self.MP = MP
        self.maxMP = MP
        self._EXP = EXP
        self.next_level_EXP = 100
        self.weapon = weapon

    def get_name(self):
        return self._name

    def set_name(self, name):
        print(f"Choisir un nom (16 caractères max.) : {name}")
        if len(name) > 16:
            print("Le nom de votre personnage doit comporter 16 caractères max")

        else:
            self._name = name
            print("Vous changez de nom pour -> {}".format(self._name))

    def get_EXP(self):
        return self._EXP

    def set_EXP(self, EXP):
        self._EXP += EXP
        self.level_up()

    def to_string(self):
        print("----------------------------------------------")
        print("Nom : {}\nNiveau : {}\nOr : {}\nPV : {}\nPM : {}".format(self._name, self.level, self.golds, self.HP, self.MP))
        print("EXP : {}\nProchain niveau : {} EXP\nObjet équipé : {}\n".format(self._EXP, self.next_level_EXP, self.weapon.name))

    def say(self, message):
        print("{} : {}".format(self._name, message))

    def equip(self, weapon):
        print("{} a été vendu(e), vous empochez {} pièce(s) d'or.".format(self.weapon.name, self.weapon.sell_price))
        self.golds = self.weapon.sell_price
        self.weapon = weapon
        print("{} équipé(e) !".format(self.weapon.name))

    def attack(self, target):
        print("{} attaque {} avec {} !".format(self._name, target._name, self.weapon.name))
        print("L'attaque inflige {} points de dégâts !".format(self.weapon.damages))

        target.HP -= self.weapon.damages

        if target.HP <= 0:
            target.die()

    def heal(self, value):
        self.HP += value
        print("{} : vous vous soignez et regagnez {} points de vie !".format(self._name, value))

    def level_up(self):
        if self._EXP >= self.next_level_EXP:
            self.next_level_EXP += 100
            self.level += 1
            print("{} monte au niveau {} !".format(self._name, self.level))
        else:
            return

    def die(self):
        if self.HP < 0:
            self.HP = 0

        print("{} succombe de ses blessures...".format(self._name))
        print("FIN DE LA PARTIE !")

    name = property(get_name, set_name)
    EXP = property(get_EXP, set_EXP)

#-------------------------------------------------------------------------------------
# PARTIE PRINCIPALE (NE PAS MODIFIER !)
#-------------------------------------------------------------------------------------

# Création des personnages
hero = Player("Joueur", 5, 3, 200, 70)
monster = Player(name = "Golem de pierre", MP = 0, weapon = Weapon("Massue", 40, 25))

# Affichage des infos des personnages
hero.to_string()
monster.to_string()

# Changement du nom du héros
hero.name = "Unnombientroplongpouretrevalide"
hero.name = "Perceval"

# Conversation entre le héros et le golem
print("\n", end='')
monster.say("Qui ose troubler mon profond sommeil ?")
hero.say("Moi ! Le héros de cette histoire !!")
monster.say("Je vois...")
hero.say("Alors en garde, vil gredin !")

# Attaque du héros contre le monstre
hero.attack(monster)
hero.attack(monster)

# Mais ce dernier se soigne et contre-attaque
monster.heal(50)
monster.heal(50)
monster.attack(hero)

# Infos des personnages mises à jour
hero.to_string()
monster.to_string()

# Notre héros trébuche sur une bosse, et découvre à moitié enterré, un arc
# Il décide de l'équiper...
thunder_bow = Weapon("Arc de foudre", 240, 350)
hero.equip(thunder_bow)

# Et balance une nouvelle attaque dévastatrice !
hero.say("Meurs, monstre !")
hero.attack(monster)

# Le héros remporte le combat et gagne de l'EXP (montée de niveau)
hero.EXP = 131
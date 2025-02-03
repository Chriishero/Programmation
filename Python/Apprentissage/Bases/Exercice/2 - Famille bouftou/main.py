"""
[Révision : héritage]

> Créer une hiérarchie de Bouftous :
    - une classe Bouftou qui possède quelques attributs (PV, PA, PM) et quelques méthodes (une par sort).
    - des classes qui héritent du Bouftou : BouftouNoir & BouftouRoyal.

> Donner vie à ces petites boules de laine :
    - créez 3 bouftous, 2 bouftous noirs et un bouftou royal.
    - utilisez un sort (de votre choix) pour chaque animal.

> Indications :
    - vous pouvez vérifier les attributs d'une classe avec une méthode supplémentaire
    - vous génèrerez un nombre aléatoire pour les PV (dans la fouchette correspondant à chaque entité)
    - pas de code à implémenter pour les sorts (mettez juste l'instruction "pass")
    - https://www.dofus.com/fr/mmorpg/encyclopedie/monstres?text=bouftou (infos générales)
    - http://wiki-dofus.eu/w/Cr%C3%A9atures_des_champs#Bouftous (pour les sorts)
"""

import random
# Générer un nombre entre 1 et 10 (inclus)
# random.randint(1, 10)

class Bouftou:
    def __init__(self, PA = 5, PM = 4):
        self.PV = random.randint(170, 280)
        self.PA = PA
        self.PM = PM

    def get_attribut(self):
        print(f"Ce Bouftou a {self.PV}PV, {self.PA}PA et {self.PM}PM.")

    def Morsure_du_bouftou(self):
        print("Morsure du bouftou !")

    attribut = property(get_attribut)

class BouftouNoir(Bouftou):
    def __init__(self):
        Bouftou.__init__(self, 5, 3)
        self.PV = random.randint(15, 27)

    def get_attribut(self):
        print(f"Ce Bouftou noir a {self.PV}PV, {self.PA}PA et {self.PM}PM.")
    
    def Morsure_du_bouftou(self):
        print("Le Bouftou noir ne possède pas le sort 'Morsure du Bouftou'.")

    def Crachouille(self):
        print("Crachouille !")
    def Mordillement(self):
        print("Mordillement !")

    attribut = property(get_attribut)

class BouftouRoyal(Bouftou):
    def __init__(self):
        Bouftou.__init__(self, 7, 5)
        self.PV = random.randint(500, 700)

    def get_attribut(self):
        print(f"Ce Bouftou royal a {self.PV}PV, {self.PA}PA et {self.PM}PM.")

    def Abolissement(self):
        print("Abolissement !")

    attribut = property(get_attribut)

b1 = Bouftou()
b2 = Bouftou()
b2 = Bouftou()

br1 = BouftouRoyal()

bn1 = BouftouNoir()
bn2 = BouftouNoir()

b1.get_attribut()
br1.get_attribut()
bn1.get_attribut()
bn2.get_attribut()

br1.Abolissement()
br1.Morsure_du_bouftou()
bn1.Crachouille()
bn2.Morsure_du_bouftou()

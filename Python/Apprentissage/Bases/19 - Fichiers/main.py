"""
Tout ce qui est lu dans un fichier est traité comme une string.
Idem pour l'écriture, ce doit être obligatoirement une string.

Modes d'ouverture : r (lecture seule)
                    w (écriture avec remplacement)
                    a (écriture avec ajout en fin de fichier)
                    x (lecture et écriture)
                    r+ (lecture/écriture dans un même fichier)
                    wb (écriture binaire)
                    rb (lecture seule binaire)

file.open(file, mode) : ouvre le fichier
file.close()     : ferme le fichier (inutile avec la syntaxe 'with')
file.read()      : récupère l'entièreté du fichier
file.readline()  : récupère qu'une seule ligne (peut être executé à la suite pour récupérer plusieurs lignes)
file.readlines() : récupère toutes les lignes restantes dans une liste
file.write()     : écris dans le fichier
file.closed()    : vérifie si le fichier est fermé

with open(file, mode) as file: : ouvre un fichier et le ferme automatiquement après le bloc conditionnel
"""

import pickle # permet d'enregistrer un fichier en code binaire

class Player:
    def __init__(self, name, level):
        self.name = name
        self.level = level

    def whoami(self):
        print(f"{self.name} ({self.level})")

p1 = Player("Chris", 99)
p1.whoami()

with open("player.data", "wb") as file:
    record = pickle.Pickler(file) # enregistre le fichier
    record.dump(p1) # copie l'objet 'p1' dans le fichier en code binaire
# le fichier se ferme automatiquement après le bloc conditionnel 'with'

with open("player2.data", "rb") as file:
    get_record = pickle.Unpickler(file) # récupère l'enregistrement du code binaire de l'objet 
    p2 = get_record.load() # charge l'enregistrement

p2.whoami()

if file.closed:
    print("Fichier fermé.")
else:
    print("Fichier encore ouvert.")
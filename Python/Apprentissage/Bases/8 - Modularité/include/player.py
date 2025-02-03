"""
Module pour le joueur
"""

def parler(personnage, message):
    print(f"{personnage} : {message}")

def au_revoir():
    print("Bye")

# permet de tester si ce module fonctionne
if __name__ == "__main__": # si le programme se lance via 'player.py' et non 'main.py'
    parler("Chris", "oui")
    au_revoir()
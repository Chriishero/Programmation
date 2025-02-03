"""
Une méthode chaine travaille sur une copie, et pas sur la chaine elle-même.

* : facultatif

str.upper() : mets en majuscule
str.lower() : miniscule
str.capitalize() : mets en majuscule la première valeur
str.title() : majuscule à chaque début de mot
str.center(<largeur>, *<caractere_remplissage>) : la largeur de la chaine sera égale à la largeur spécifié
Le caractère spécifié, ou les espaces, seront mis à gauche et à droite de la chaine initial.

str.find(<chaine>, *<debut>, *<fin>) : renvoie l'index de la chaine, et -1 si il ne trouve pas
str.index(<chaine>, *<debut>, *<fin>) : renvoie l'index de la chaine, et un exception si il ne trouve pas
str.strip() : enlève les espaces indésirable au début et à la fin de la chaine
str.replace(<ancienne>, <nouvelle>, *<occurences>)
str.split(<séparateur>) : sépare la liste à partir d'un séparateur

str.isalpha(), str.isdigit(), str.isdecimal(), str.isnumeric(), str.isalphanum()
str.islower(), str.isupper()
str.isidentifier() : vérifie si c'est un mot réservé de Python
str.iskeyword()
"""

string = "hello world !"
print(string.find("world"))

string = string.replace("hello", "goodbye")
print(string.capitalize())
print(string.split(" "))

if "hello" in string:
    print(f"{string} contient 'hello'")
else:
    print(f"'{string}' ne contient pas 'hello'")
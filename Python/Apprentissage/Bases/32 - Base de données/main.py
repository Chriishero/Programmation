"""
SQLite a pour utilité de remplacer les fichiers textes, par des bases de données légères.
Il n'est pas à utiliser si on veut gérer énormément de quantité de données (>=1go), il faudra utiliser MySQL.
Dans des bases de données >=1to, il faudra utiliser PostgreSQL

CRUD : Create, Read, Update, Delete

cursor.execute() : gère une seule information (requête)
cursor.executemany() : gère plusieurs information
cursor.fetchone() : récupère, liste les informations sous forme d'une seule donnée
cursor.fetchall() : récupère une liste de toutes les informations

connection.commit() : valide toutes les modifications de la DB
"""

import sqlite3

try:
    connection = sqlite3.connect("basepy.db") # se connecte à la base de données, en créer une nouvelle si inexistante
    cursor = connection.cursor() # créer une instance de la classe 'cursor', les requêtes sont possible grâce à ce curseur

    my_username = ("Chris",)
    cursor.execute("SELECT * FROM tt_users WHERE user_name = ?", my_username) # selectionne toutes les info de la base de donnée 'tt_users', dans le cas où 'user_name' = Chris
    result = cursor.fetchone()[1]
    print(f"Le nom d'utilisteur est : {result}")

    """
    new_user = (cursor.lastrowid, "Jason", 23)
    cursor.execute("INSERT INTO tt_users VALUES(?,?,?)", new_user) # insère à l'intérieur de la DB 'tt_user', les valeurs suivantes
    connection.commit() # valide les changements de la DB
    """

    req = cursor.execute("SELECT * FROM tt_users")

    for row in req.fetchall():
        print(row[1])

except Exception as e: # renvoie l'exception dans la variable 'e'
    print(f"[ERROR] {e}")
    connection.rollback() # revient à la dernière validation de la DB (.commit())

finally:
    connection.close() # se déconnecte de la base de données
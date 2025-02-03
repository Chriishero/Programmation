"""
Python ne fait pas de différence entre une information GET et une information POST.
GET : envoie les données dans l'url (pour récupèrer)
POST : envoie les données dans le corps de la requête, comme un formulaire (pour envoyer)
"""

import cgi

print("Content-type: text/html; charset=utf-8\n") # cet entête précise explicitement que l'affichage des lignes suivantes est de type html 

html = """<!DOCTYPE html>
<head>
    <meta charset="utf-8">
    <title>Page web depuis un serveur python HTTP</title>
</head>
<body>
    <h1>Page Web ave Python CGI et données formulaire</h1>
    <form methode="post" action="result.py">
        <p><input type="text" name="username">
        <input type="submit" value="Envoyer">
    </form>
</body>
</html>
"""
# <form methode="post" action="result.py"> : permet de renseinger le script python formulaire, la page sera redirigé vers ce script

print(html)
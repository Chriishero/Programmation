"""
expires : date d'expiration du cookie : Sat, jj-mm-yy 12:02:52
path : lien du cookie
comment : commentaire du cookie
domain : domaine du site
secure : le cookie fonctionne uniquement sur une connexion HTTPS
version : version du cookie
httponly : empêche l'exploitation du cookie en javascript

Set-Cookie: pref_lang=fr; httponly : entête pour la création de cookie

Le cookie peut être créé ave un 'print', mais doit l'être AVANT l'entête html

HTTP_COOKIE : variable d'environnement qui enregistre tous les cookies
"""

import cgi
import http.cookies
import datetime
import os
import sys
import codecs

sys.stdout = codecs.getwriter("utf-8")(sys.stdout.detach()) # modifie l'encodage en écriture de la sortie standard

expiration = datetime.datetime.now() + datetime.timedelta(days=365) # l'expiration sera dans 1 ans à partir de maintenant
expiration = expiration.strftime("%a, %d-%b-%Y %H:%M:%S") # format obligatoire pour l'argument 'expires' d'un cookie

my_cookie = http.cookies.SimpleCookie() # créer un cookie simple
my_cookie["pref_lang"] = "fr"
my_cookie["pref_lang"]["expires"] = expiration
my_cookie["pref_lang"]["httponly"] = True # charge l'argument 'httponly' dans le cookie 'pref_lang'

print(my_cookie.output()) # génère le cookie
print("Content-type: text/html; charset=utf-8\n") # cet entête précise explicitement que l'affichage des lignes suivantes est de type html 
print(my_cookie.output()) # affiche le cookie car il est après l'entête HTML

html = """<!DOCTYPE html>
<head>
    <meta charset="utf-8">
    <title>Page web depuis un serveur python HTTP</title>
</head>
<body>
    <h1>Cookies avec Python</h1>
"""
print(html)

try:
    user_lang = http.cookies.SimpleCookie(os.environ["HTTP_COOKIE"]) # récupère tous les cookies stockés dans la variable d'environnement 'HTTP_COOKIE'
    print("La langue choisit par l'utilisateur est : ", user_lang["pref_lang"].value) # affiche la valeur de l'argument 'pref_lang' du cookie récupéré
except(http.cookies.CookieError, KeyError): # exception possible lors d'une erreur d'extraction d'un cookie
    print("Cookie non trouvé.")

html = """<p> Accent : é, è, ê</p>
</body>
</html>
"""
print(html)
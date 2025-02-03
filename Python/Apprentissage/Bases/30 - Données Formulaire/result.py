import cgi
import cgitb

cgitb.enable() # active le mode debug, à désactiver lors de la mise en ligne du site
form = cgi.FieldStorage() # récupère l'ensemble des informations d'un formulaire transmis

print("Content-type: text/html; charset=utf-8\n") # cet entête précise explicitement que l'affichage des lignes suivantes est de type html 
html = """<!DOCTYPE html>
<head>
    <meta charset="utf-8">
    <title>Page web depuis un serveur python HTT</title>
</head>
    <h1>Page de résultats</h1>
"""
print(html)

try:
    if form.getvalue("username"): # si le champ de formulaire, 'input', 'username' existe
        username = form.getvalue("username")
        print(f"<p>Bonjour {username} !</p>")
        print("<script>alert('ok')</script>") # code javascript qui permet de mettre un popup de contenue 'ok'
    else:
        raise Exception("Pseudo non transmis.")
except:
    print("Pseudo non transmis.")

html = """
</body>
</html>
"""
print(html)
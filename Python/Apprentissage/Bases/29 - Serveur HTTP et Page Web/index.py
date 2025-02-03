import cgi

print("Content-type: text/html; charset=utf-8\n") # cet entête précise explicitement que l'affichage des lignes suivantes est de type html 

html = """<!DOCTYPE html>
<head>
    <meta charset="utf-8">
    <title>Page web depuis un serveur python HTTP</title>
</head>
<body>
    <h1>Coucou</h1>
    <p>Contenue HTML</p>
</body>
</html>
"""

print(html)
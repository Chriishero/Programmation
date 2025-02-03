"""
handler = http.server.SimpleHTTPRequestHandler : gestionnaire de requête HTTP simple (exécute des fichiers html/css)
httpd = socketserver.TCPServer(adress, handler) : créer le serveur HTTP avec le module socketserver 

handler = http.server.SimpleHTTPRequestHandler : gestionnaire de requête HTTP CGI (exécute des scripts)
CGI : interface qui permet d'exécuter les fichiers et retourner le résultats sur un serveur
"""

import http.server

port = 80 # port de la communication
address = ("", port)

server = http.server.HTTPServer

handler = http.server.CGIHTTPRequestHandler # gestionnaire de requête HTTP CGI
handler.cgi_directories = ["/"] # liste de répertoires où se trouve les scripts à exécuter

httpd = server(address, handler)

print(f"Serveur démarré sur le port {port}")

httpd.serve_forever() # lance le serveur en boucle jusqu'à la fermeture du programme
"""
Il faut encoder les informations en utf-8 avant l'envoie, et les décoder avant la réception
"""
import socket

host, port = ("localhost", 4444) # renseigne l'host et le port du serveur
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    socket.connect((host, port)) # connect le client au serveur
    print("Client connecté.")

    data = "Ceci est un message venant d'un client, éèçîö."
    data = data.encode("utf8")
    for i in range(10):
        socket.sendall(data)

except ConnectionRefusedError: # cette exception est levé quand le client essaye de se connecter sans avoir démarré le serveur
    print("Le serveur n'est pas démarré.")
except Exception as e:
    print("[ERROR]", e)

finally:
    socket.close()
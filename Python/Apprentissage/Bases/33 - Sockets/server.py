"""
TCP : sert à établir une connexion avec une autre machine pour communiquer
UDP : permet de communique sans se connecter directement et sans aucune vérification (plus rapide, moins fiable)

Il faut encoder les informations en utf-8 avant l'envoie, et les décoder avant la réception
"""

import socket
import threading

class ClientsThread(threading.Thread): # permet les connexions multiples sur le serveur, chaque client sera relié à un thread pour ne pas mettre en attente les autres

    numeroClient = 0

    def __init__(self, conn):
        threading.Thread.__init__(self)
        self.conn = conn
        ClientsThread.numeroClient += 1

    def run(self):
        data = self.conn.recv(1024) # récupère les données reçu avec un buffer de taille 1024
        data = data.decode("utf8")
        print(f"Client {ClientsThread.numeroClient} : {data}")


host, port = ("", 4444)

socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # créer un socket de famille 'AF_INET' et de type 'SOCK_STREAM'
socket.bind((host, port)) # associe le socket à un adresse et un port, prend un tuple en paramètre
print("Le serveur est démarré.")

while True:
    socket.listen() # mets en écoute le port sur l'adresse, en paramètre le nombre de connexion échoué avant d'en refuser d'autre (optionnel)
    conn, address = socket.accept() # accepte les connexions dans la variable 'conn', et stock l'adresse et le port dans 'address'
    print("Un client vient de se connecter.")

    my_thread = ClientsThread(conn)
    my_thread.start()

conn.close()
socket.close()
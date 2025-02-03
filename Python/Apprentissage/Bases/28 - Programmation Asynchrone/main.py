"""
De base, un programme s'execute de manière séquentielle, chaque ligne après les autres dans un seul file.
La programmation asynchrone permet de crée des files différents pour les executer en même temps

th = threading.Thread(target=function, *name=name)
"""

import threading
import time

my_lock = threading.RLock() # crée un verrou qui permet de bloquer l'exécution des autres threads si le programme du thread actuel atteint un point 'critique'

class MyProcess(threading.Thread): # cette classe hérite de 'threading.Thread'
    def __init__(self):
        threading.Thread.__init__(self) # surcharge le constructeur de la classe 'threading.Thread'

    def run(self): # surcharge la méthode 'run' de la classe mère 'threading.Thread'
        i = 0 
        while i < 3:
            with my_lock: # avant que le prochain thread s'execute, ce code sera exécuté
                letters = "ABC"
                for l in letters:
                    print(f"{threading.current_thread()} : {l}")
                    time.sleep(0.3)
            i += 1

th1 = MyProcess()
th2 = MyProcess()

th1.start() # lance le thread 'th1'
th2.start()

th1.join() # bloque le programme jusqu'à la fin d'exécution du thread
th2.join()

print("Fin du programme.")
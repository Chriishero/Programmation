import time

"""
time.sleep(n) : met en pause le processus (thread) pendant 'n' seconde(s).

En informatique, le temps à commencé le 1er Janvier 1970 à 00h00.
time.time() : permet d'afficher le nombre de seconde écoulé depuis (TIMESTAMP)
time.localtime() : renvoie la date actuel sous une structure de temps depuis le TIMESTAMP
time.mktime() : renvoie le TIMESTAMP depuis le 'localtime'

Format de date : 
%d : jours (01 à 31)
%m : mois (01 à 12)
%Y : année (ex : 2024) - %y (00 à 99)
%H : heures (00 à 23)
%I : minutes (00 à 59)
%S : secondes (00 à 59)
%p : AM/PM

%A : jour semaine / %a (jour abrégé)
%B : mois / %b (mois abrégé)

%Z : fuseau horaire (timezone)
"""

print(time.strftime("%Z"))

tps = time.localtime()
print(tps)
tps = time.mktime(tps)
print(tps)

begin = time.time()
print("Début.")

time.sleep(3)

end = time.time()
print(f"Temps écoulé : {end - begin}s")
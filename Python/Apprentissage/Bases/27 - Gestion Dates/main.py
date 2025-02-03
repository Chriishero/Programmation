import datetime

"""
datetime.datetime() : année, mois, jour, heure, minute, seconde
        .datetime.now() : renvoie la date actuel
        .date.today() : renvoie la date actuel
        .date() : année, mois, jour   
        .time() : heure, minute, seconde


'datetime' hérite de la classe 'date'
"""

d1 = datetime.datetime(2024, 12, 30, 15, 14, 2) # créer un objet de date : année, mois, jour, heure, minute, seconde
d2 = datetime.datetime(2024, 12, 2, 2, 56, 25)

if d1 > d2:
    print("d1 est plus récent que d2")
else:
    print("d2 est plus récent que d1")

print(d1.year)
print(datetime.datetime.now())
print(datetime.datetime.today())
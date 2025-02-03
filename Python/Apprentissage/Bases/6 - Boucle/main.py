"""
for i in range(0, 10, 1) : itère de 0 à 10, en faisant des pas de 1
0 et 1, sont optionnelles, ils sont par défaut à cette

for i,j in zip(list1, list2) : itère dans plusieurs listes en même temps, l'itération s'arrêtera là où la liste la plus courte s'arr$ete
"""

# boucle for
for num_client in range(1, 6):
    print("Vous etes le client n°", num_client)
print("/////////////////////////////////////////////////////////////////////////////////////")

# lister les emails
emails = ["chrisvilleneuve@icloud.com", "christianvilleneuve@icloud.com", "denial.service@yahoo.com", "chrisvdraw@yahoo.com", "louki.villeneuve@gmx.fr"]

# blacklist
blacklist = ["chrisvilleneuve@icloud.com", "denial.service@yahoo.com"]

# pour chacune des valeurs, j'affiche "Email envoyé à [INSERER L'EMAIL]
for email in emails:

    if email in blacklist:
        print("Email {} interdit ! Envoie impossible.".format(email))
        continue
        # ou sinon "Break" pour casser la boucle

    print(" Email envoyé à : ", email)
print("////////////////////////////////////////////////////////////////////////////////////////////////////////////")

# while : tant qu'une condition est vrai
salary = 1500

# tant que le salaaire < 2000€, + 120€
while salary < 2000:
    # ajouter 120€ au salaire
    salary += 120
    # afficher le résultat
    print("Voter salaire actuelle est de ", salary, "€")

print("Fin du programme")
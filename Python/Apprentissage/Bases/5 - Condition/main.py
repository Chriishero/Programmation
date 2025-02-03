
password = input("Entrer un mot de passe")
password_lenght = len(password)

if password_lenght <=8:
    print("Mot de passe trop court ! ")

elif 8> password_lenght <=12:
    print("Mot de passe moyen ! ")

else:
    print("Mot de passe parfait ! ")

print("Voter mot de passe fait ", str(password_lenght), " caractères ")
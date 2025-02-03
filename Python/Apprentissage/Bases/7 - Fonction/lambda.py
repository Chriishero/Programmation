"""
Une fonction lambda en python permet d'executer une seule instruction.

f = lambda x: x**2 : revient à dire f(x) = x²
"""

# stock la fonction lambda dans une variable pour pouvoir l'utiliser
lambdaVar = lambda:print("Hello world ! ")

# fonction lambda qui retourne le quotient de 'a' et 'b'
lambdaDivision = lambda a, b : a / b 

lambdaVar()
print(lambdaDivision(1, 2))
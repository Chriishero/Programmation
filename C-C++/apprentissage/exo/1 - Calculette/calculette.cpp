#include <iostream>
#include <string>

/*
> Écrire un programme de calculatrice simple pour 2 nombres :
    - afficher un menu principal proposant les 4 types de calcul (+, -, * et /) ou de quitter.
    - une fois le calcul choisi, demander la saisie de 2 nombres et afficher le résultat.
    - rediriger sur le menu principal

> Indications : 
    - utiliser au maximum des fonctions (pour optimiser votre code et éviter les répétitions).
    - vérifier que la saisie au menu est correct, sinon redemander une saisie.
    - vérifier que les nombres saisis sont compris entre -1000 et 1000. 
*/

void number_choice(float& a, float& b)
{
    while (1)
    {
        std::cout << "Choose a first number : ";
        std::cin >> a;
        if (a > 1000 || a < -1000)
        {
            std::cout << "Choose a number between -1000 and 1000." << std::endl;
            continue;
        }
        
        std::cin.ignore(255, '\n');
        std::cout << "Choose a second number : ";
        std::cin >> b;

        if (b > 1000 || b < -1000)
        {
            std::cout << "Choose a number between -1000 and 1000." << std::endl;
            continue;
        }

        else {break;}
        
    }
}

float sum(float a, float b)
{
    return a + b;
}

float subtraction(float a, float b)
{
    return a - b;
}

float multiplication(float a, float b)
{
    return a * b;
}

float division(float a, float b)
{
    return a / b;
}

float modulo(int a, int b)
{
    return a % b;
}

int main()
{
    float a, b;

    while (1)
    {
        char choice;
        std::cout << "Sum : + \nSubtraction : - \nMultiplication : * \nDivision : / \nModulo : % \nExit : 0" << std::endl;

        std::cout << "Choose your calculation methode : ";
        std::cin >> choice;

        if (choice == '+')
        {
            number_choice(a, b);
            std::cout << a << " + " << b << " = " << sum(a, b) << "\n" << std::endl;
            continue;
        }

        else if (choice == '-')
        {
            number_choice(a, b);
            std::cout << a << " - " << b << " = " << subtraction(a, b) << "\n" << std::endl;
            continue;
        }
        
        else if (choice == '*')
        {
            number_choice(a, b);
            std::cout << a << " * " << b << " = " << multiplication(a, b) << "\n" << std::endl;
            continue;
        }

        else if (choice == '/')
        {
            number_choice(a, b);
            std::cout << a << " / " << b << " = " << division(a, b) << "\n" << std::endl;
            continue;
        }

        else if (choice == '%')
        {
            number_choice(a, b);
            std::cout << a << " % " << b << " = " << modulo(a, b) << "\n" << std::endl;
            continue;
        }

        else if (choice == '0')
        {
            break;
        }

        else {std::cout << "Choose one of the choice." << std::endl; continue;}

    }

    return 0;    
}
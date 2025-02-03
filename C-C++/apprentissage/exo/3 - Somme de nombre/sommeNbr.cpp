#include <iostream>

/*
> Écrire un programme qui calcule la somme des entiers d'un
  nombre à un autre (maximum : entre 1 et 1000)

> Indications :
    - prévoir le cas où "min" serait plus grand que "max" et quitter
      le programme si ça arrive.
    - prévoir le cas où "min" sera plus petit que 1 et "max" plus grand 
      que 1000
*/

int main(void) 
{
    int min, max, sum;

    std::cout << "Entrez un nombre minimal : ";
    std::cin >> min;
    std::cin.ignore(255, '\n');
    std::cout << "Entrez un nombre maximal : ";
    std::cin >> max;

    if (min > max)
    {
        std::cout << "Le minimum doit être plus petit que le maximum";
        return -1;
    }

    else if (min < 1)
    {
        std::cout << "Le minimum doit être supérieur ou égale à 1";
        return -1;
    }
    
    else if (max > 1000)
    {
        std::cout << "Le maximum doit être inférieur ou égale à 1000";
        return -1;
    }
    
    else if (min < max)
    {
        for (int i = min; i <= max ; i++)
        {
            sum += i;
        }
    }
        
    else
    {
        std::cout << "Saisie incorrecte.";
        return -1;
    }

    std::cout << "La somme final est : " << sum;

    return 0;
}
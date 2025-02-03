#include <iostream>
#include <string>

int main(){

    int number{-15454545};

    std::cout << number << std::endl;

    { // ce bloc à un accès au bloc externe, mais l'externe n'a pas accès à ce bloc interne
        int other_number{4}; 
    }


    /*if(number < 20 && number >= 0) //ne rien mettre équivaut à == true 
    { 
        std::cout << "Entre 0 et 19" << std::endl;
    }

    else if (number >= 20)
    {
       std::cout << "Superieur ou egale a 20" << std::endl;
    }

    else
    {
        std::cout << "Nombre negatif" << std::endl;
    } */

    /* int code{0}; 
    std::cout << "Entez un chiffre : ";
    std::cin >> code; 

    switch(code)
    {
        case 1:
            // std::cout << "Vous avez saisi 1" << std::endl;
        case 2:
            std::cout << "Vous avez saisi 1 ou 2" << std::endl;
            break; // permet de sortir de switch et éviter que le programme vérifie les autres cas

        case 3:
            std::cout << "Vous avez saisi 3" << std::endl;
            break;
        default: // équivalent à else
            std::cout << "Different de 1, 2 et 3" << std::endl;
            break; 
    } */


    return 0;
}
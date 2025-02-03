#include "vecteur.hpp"
#include <iostream>
#include <cmath> // inclue des opérations mathématique tel que la racine carré

int main()
{

    Vecteur v1("u", 2, 5, "horizontal", "droite");
    Vecteur v2("v", -55, 5, "horizontal", "droite");

    std::cout << v1 << std::endl;
    std::cout << std::endl;
    std::cout << v2 << std::endl;

    std::cout << '\n' << v1 * v2 << std::endl; // produit scalaire

    return 0;
}
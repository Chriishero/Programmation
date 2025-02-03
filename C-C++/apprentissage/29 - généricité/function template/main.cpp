#include "number.hpp"
#include <iostream>
#include <string>

int main()
{
    auto r1 = sum(5, 8); // le compilateur déduis le type de la fonction, sauf en cas de conflit
    std::cout << r1 << std::endl;

    auto r2 = sum<double>(2, 9.6); // possibilité d'indiquer explicitement le type de la fonction, <double>
    std::cout << r2 << std::endl;

    auto r3 = sum<>(6, 2); // <> indique qu'il faut utiliser le type par défaut définie dans le fichier.hpp
    std::cout << r3 << std::endl;

    return 0;
}
#include "utils.hpp"
#include <iostream>

void Util::test()
{
    std::cout << "Fonction test de l'espace de nom Util" << std::endl;
}

void Util::subUtil::test2()
{
    std::cout << "Fonction test2 de l'espace de nom subUtil de l'espace de nom Util" << std::endl;
}
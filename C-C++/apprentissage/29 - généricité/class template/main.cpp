#include "container.hpp"
#include <iostream>
#include <string>

int main ()
{
    DataContainer<int, std::string> dc1{25, "Oui"}; // indication explicité des types de la classe 'int' et 'std::string'
    std::cout << dc1.getN() << std::endl;
    std::cout << dc1.getM() << std::endl;

    DataContainer<std::string, double> dc2{"Hello", 5.6}; // indication explicité des types de la classe 'std::string' et 'double'
    std::cout << dc2.getN() << std::endl;
    std::cout << dc2.getM() << std::endl;

    return 0;
}
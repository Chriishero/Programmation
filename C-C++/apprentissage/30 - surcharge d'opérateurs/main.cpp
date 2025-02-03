#include "time.hpp"
#include <iostream>

/*
    La surcharge d'opérateur permet d'écrire la manière dont les opérateurs en C++ vont intéragir avec les types primitifs/personnalisés

    objet.operator<<(argss) : c'est un type de syntaxe rarement utilisé pour utiliser les opérateurs
*/

int main()
{
    jc::Time t1{14, 25, 56};
    jc::Time t2{03, 20, 3};

    std::cout << t1 << std::endl; // la surcharge d'opérateur permet d'afficher directement l'objet 't1' sans passer par des méthodes accesseurs
    std::cout << t2 << std::endl;
    std::cout << t1 + t2 << std::endl; // t1 fais appelle à la méthode 'operator+' avec t2 en argument
// = std::cout << t1.operator+(t2) << std::endl;

    std::cout << t1 + 23 << std::endl;

    return 0;
}
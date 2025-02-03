#include "someone.hpp"
#include "english.hpp"
#include "french.hpp"
#include <iostream>
#include <string>

int main()
{

    // Exemple type de l'utilisaton du polymorphisme : 
    /*
        Déclarer une liste, un tableau, ... de "Someone", initialisé avec plusieurs objets dérivés (English, French, etc.)

        Pour chaque "Someone" de la liste/du tableau, 
        faire appel à la méthode 'sayGoodNight()'
    */
   
    English en{"Chris"};
    en.sayGoodNight();

    French fr{"Ivan"};
    fr.sayGoodNight();

    return 0;
}
#include "someone.hpp"
#include "english.hpp"
#include "french.hpp"
#include <iostream>
#include <string>
#include <vector>

int main ()
{
    English en1{"Bryan"};
    English en2{"Chris"};

    French fr1{"Ivan"};
    French fr2{"Julie"};

    std::vector<Someone> people{}; // Créer un tableau de type de classe 'Someone', et permet de stocker des valeurs de sous-classes de 'Someone'
    // En C++, on ne peut pas stocker des éléments d'une classe abstraite, car std::vector a besoin de la taille des types concret et une classe abstraite n'est pas concret
    
    people.push_back(en1);
    people.push_back(en2);
    people.push_back(fr1);
    people.push_back(fr2);

    for(const auto& p : people)
    {
        std::cout << p.sayGoodNight() << std::endl;
    }

    return 0;
}
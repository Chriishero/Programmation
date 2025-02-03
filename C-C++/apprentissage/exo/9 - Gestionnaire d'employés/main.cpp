#include "employe.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{

    Employe e1{"Millet", "Julie", 2000};
    Employe e2{"Ayache-Audibert", "Ivan", 1500};
    Employe e3{"Villeneuve", "Christian", 6000};

    std::vector<Employe> employe_vec{e1, e2, e3};
    
    std::sort(std::begin(employe_vec), std::end(employe_vec), salary_sort); // appelle la fonction 'salary_sort', sans les '()' pour fournir seulement la référence (adresse) à la fonction, et non l'appeler
    // le 3ème argument est un pointeur de fonction qui représente une fonction de comparaison

    for (const auto& e : employe_vec)
    {
        std::cout << e << "\n" << std::endl;
    }

    if(e1 == e2)
    {
        std::cout << "\nIls gagnent le meme salaire." << std::endl;
    }
    else if (e1 > e2)
    {
        std::cout << "\n" << e1.get_first_name() << " gagne " << e1.get_salary() - e2.get_salary() << "e de plus que " << e2.get_first_name() << "." << std::endl;
    }
    else if (e1 < e2)
    {
        std::cout << "\n" << e2.get_first_name() << " gagne " << e2.get_salary() - e1.get_salary() << "e de plus que " << e1.get_first_name() << "." << std::endl;
    }

    return 0;
}
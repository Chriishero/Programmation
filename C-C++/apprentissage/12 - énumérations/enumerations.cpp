#include <iostream>

/*
   enum NomEnumeration = l'énumération est régulière et a une porté global
   enum class/struct NomEnumeration = l'énumération est étendu et a une porté local 
   
   enum NomEnumeration : type = permet de donner un type au valeur de l'énumération, char et tous les integers fonctionnent
*/

enum NaturalElement : int // permet de définir un type et peut posséder une des valeurs listés (earth, air, fire, water) dans un ensemble défini (NaturalElement)
{ 
    earth = 0, // 0
    air,   // 1
    fire,  // 2
    water  // 3
}; 

enum class OtherElement
{
    dark,
    light
};

enum class smallint : int{}; // smallint est un type sous-jacent à int, une copie 

int main()
{
    NaturalElement ne{water};
    OtherElement oe{OtherElement::dark}; // NomEnumeration::valeur est nécessaire si l'énumération est local (class/struct)

    std::cout << ne << std::endl;
    std::cout << static_cast<int>(oe) << std::endl; // La conversion en entier doit être fait explicitement

    if (ne == water)
    {
        std::cout << "Oui ! ne == water" << std::endl;
    }
    
    if (oe == OtherElement::dark)
    {
        std::cout << "Oui ! oe == dark" << std::endl;
    }
    

    return 0;
}
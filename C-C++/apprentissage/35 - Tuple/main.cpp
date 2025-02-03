#include <iostream>
#include <string>
#include <tuple>

/*
    Tuple : collection hétérogène de taille fixe, un tuple peut stocker des informations de types différents.
            C'est un mélange entre un struct et un std::array.
    Un tuple est à la structure ce que la lambda est à la fonction, elle est surtout utile dans une porté locale

    std::tuple : au version antérieur à C++17, il faut spécifier les types avec <type>
    std::make_tuple : pour toutes les versions, le compilateur déduit implicitement les types utilisé

    std::get<i>(myTuple) : récupère l'élément 'i' du tuple 'myTuple'

    Si 'i' est le seul dans le tuple à avoir ce type, on peut utiliser get avec son typename : 
    std::get<typename>(myTuple)
*/

using namespace std::literals; // obligatoire pour que le type déduit soit bien un std::string dans un tuple et non des chaînes héritées du C

std::tuple<std::string, std::string, int> returnTuple() // doit préciser les types pour renvoyer le tuple
{
    return std::make_tuple("Louki"s, " a "s, 9);
}

int main()
{    
    std::tuple info = std::make_tuple( "Chris"s, 5); 

    std::cout << "Prénom : " << std::get<0>(info) << ", Age : " << std::get<1>(info) << std::endl;

    std::get<int>(info) = 10; // s'il n'y a qu'une seule information de ce type, il peut être récupérer avec son typename
    std::cout << "Prénom : " << std::get<0>(info) << ", Age : " << std::get<int>(info) << std::endl;
    
    auto infoLouki = returnTuple();
    std::cout << std::get<0>(infoLouki) << " a " << std::get<2>(infoLouki) << " ans";

    return 0;
}
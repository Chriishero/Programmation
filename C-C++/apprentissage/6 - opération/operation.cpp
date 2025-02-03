#include <iostream>

/*
    Arithmétique : + - * / %
    Booléens     : ! (not) && (and) || (or) : ordre de priorisation , not > and > or
    Comparaison  : < <= > >= == !=
    Divers       : += -= *= /= %= ++ --

    data = 0
    data++ : data + 1 -> 1
    ++data : 1 + data -> 1

    result = data++; // result = 0 / data = 1
    result = ++data; // data + 1 / result <- data
*/

int main(){

    /* int result;
    result = (1 + 2) * 3;

    bool result;
    result = true; Vrai
    result = true && false; Vrai et Faux = Faux
    result = !true; Négation de Vrai = Faux

    int level_player{1};
    std::cout << "Niveau actuel : " << level_player << std::endl;

    level_player = level_player + 1;
    level_player += 1;

    level_player++;

    std::cout << "Niveau actuel : " << level_player << std::endl; */

    auto data{0};
    auto result{0};

    result = data++; // le +1 occure sur data APRES l'affectation de data à result

    std::cout << "Result : " << result << std::endl;
    std::cout << "Data : " << data << std::endl;

    return 0;
}
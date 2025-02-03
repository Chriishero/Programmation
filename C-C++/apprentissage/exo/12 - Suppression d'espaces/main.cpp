#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string sentence = "\f If you were God, and your delusions could become reality,\n";
    std::cout << sentence;

    // pour supprimer les espaces de fin, on peut aussi inverser la chaine avec 'std::reverse' pour les mettre au début, les supprimer, et la remettre à l'endroit initial avec 'std::reverse'
    auto beginSpace { std::find_if_not(std::rbegin(sentence),  std::rend(sentence), isspace) };
    sentence.erase(beginSpace.base(), std::end(sentence)); // 'base()' convertie l'intérateur inversé en intérateur normal
    std::cout << sentence;

    auto endSpace { std::find_if_not(std::begin(sentence), std::end(sentence), isspace) };
    sentence.erase(std::begin(sentence), endSpace);
    std::cout << sentence;

    return 0;
}
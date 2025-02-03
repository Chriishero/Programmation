#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string phrase = "Ceci est un exemple d'exercice trouve dans un livre.";

    auto begin = std::begin(phrase);
    auto space = std::find(begin, std::end(phrase), ' ');

    auto i_space = std::count(begin, std::end(phrase), ' ');

    for(auto i = 0; i < i_space; i++)
    {
        std::string mot {begin, space};
        auto total_premier_mot = std::count(begin, space, 'e');

        std::cout << "dans le mot : '" << mot << "', il y a : " << total_premier_mot << " e" << std::endl;
        
        begin = ++space; // incrémente l'espace car si le première pointeur est un espace, il pointera à nouveau sur cet espace
        space = std::find(begin, std::end(phrase), ' ');
    }
    
    
    return 0;
}
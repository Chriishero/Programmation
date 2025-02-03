#include <iostream>
#include <string>
#include <string_view> // Entête de std::string_view

/*
    Une chaine de caractère 'string' est un tableau de caractère :
    "Bonjour" : "B", "o", "n", "j", "o", "u", "r", "\0"
    "\0" : carctère de fin

    std::string -> std::basic_string<char>

    std::string_view : chaine de caractère en lecture seul, qui garanti de ne pas générer d'erreur (noexcept), c'est une référence (&) constante (const) vers autre chose

    std::size(), std::empty()
    stringName[i], at(), front(), back(), push_back(), pop_back(),
    append(), clear(), size(), lenght(), starts_with(), ends_with(),
    contains()
    substr() : string.substr(n)    : ignore les n premiers caractères de la chaine 'string'
               string.substr(n, x) : ignore les n premiers caractères et lis les x prochains

    swap() : string1.swap(string2) : inverse les valeurs de 'string1' et 'string2'

*/

int main()
{
    std::string s{"Bonjour"}; // std::string est équivalent à std::basic_string<char>
    std::string_view sv{s}; // Référence constante à 's'

    s.append(2, '!'); // Ajoute 2 '!' à la fin de la chaine de caractère 's'

    std::cout << "Premier caractere : " << s[0] << std::endl; // Affiche le caractère qui se trouve à l'indice 0 de la chaine de caractère 's'
    std::cout << s << std::endl;

    for (const auto& c : s) // Pour chaque caractère de la chaine 's'
    {
        std::cout << c << std::endl;
    }

    if(s.starts_with('B')) // s.starts_with('Bon') fonctionne aussi
    {
        std::cout << s << " commence par 'B'" << std::endl;
    }

    if(s.contains("onj"))
    {
        std::cout << s << " contient 'onj'" << std::endl;
    }

    return 0;
}
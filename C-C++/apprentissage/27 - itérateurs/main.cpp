#include <iostream>
#include <string>
#include <vector> 
// #include <iterator> ce fichier d'en-tête est déjà inclue avec les conteneurs utilisés

/*
    Les itérateurs permettent de parcourir un conteneur.

    Itérateur non constant : on peut déplacer le curseur (itérateur), on peut modifier les éléments
        std::typeConteneur::iterator it{endroitPointé};
        *it = newValue; 
        it = std::next(it);

    Itérateur constant : on peut déplacer le curseur
        std::typeConteneur::const_iterator it{endroitPointé};
        it = std::next(it); est possible

    Itérateur déclaré constant : on peut modifier les éléments (du conteneur)
        const std::typeConteneur::iterator it{endroitPointé};
        *it = 'A'; est possible, modifie l'élément pointé par l'itérateur

    Itérateur constant déclaré constant : /
        const std::typeConteneur::const_iterator it{endroit pointé};

    std::begin(), std::end()
    std::cbegin(), std::cend() : garanti l'itérateur d'être constant
    std::next(), std::prev()   : déplace l'itérateur

    std::rbegin() : parcours de la fin vers le début du conteneur
    std::rend()   : parcours du début vers la fin
*/

int main()
{
    using namespace std::literals; // permet l'ajoute du suffixe 's' devant une string
    // donc de considérer std::string comme une string, et non du char

    std::string sentence{"Hello world !"s};
    std::string::iterator it{std::begin(sentence)}; // l'itérateur (curseur) pointe sur le début de la string 'sentence'.

    std::cout << *it << std::endl; // affiche la valeur pointé par l'itérateur, ici c'est 'H'
    *it = 'A'; // modifie la valeur pointé par l'itérateur
    std::cout << *it << std::endl;
    it = std::next(it); // déplace l'itérateur au prochain élément avec 'next'
    std::cout << sentence[0] << std::endl;

    std::string::const_iterator it2{std::begin(sentence)}; // itérateur constant
    const std::string::iterator it3{std::begin(sentence)}; // itérateur déclaré constant
    const std::string::const_iterator it4{std::begin(sentence)}; // itératuer constant déclaré constant

    std::vector<int> vec{1, 2, 3, 4, 5};
    std::vector<int>::iterator itvec{vec.begin()}; // auto est possible

    for(auto it = std::begin(vec); it != std::end(vec); it++) // it++ : it = std::next(it)
    // équivalent à for(auto& element : vec)
    // ce genre de boucle rend le code générique, cette boucle est compatible avec tous les conteneurs et types
    {
        std::cout << *it << std::endl;
    }

    return 0;
}
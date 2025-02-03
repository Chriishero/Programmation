#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
    Les algorithmes sont génériques, fonctionnels sur tous les types différents.

    it1 = begin
    it11 = end

    std::fill(it1, it1, value)       : remplissage dans une tranche précise, entre 2 itérateurs
    std::equal(it1, it11, it2, it22) : vérifie l'égalité de 2 conteneurs, 2 itérateurs du conteneur 1, 2 du conteneur 2
    std::find(it1, it2, value)       : cherche un élément dans une tranche précise, entre 2 itérateurs
    std::search(it1, it11, it2, it22): recherche d'un ensemble d'élément dans un conteneur
    std::count(it1, it11, value)     : compte le nombre d'occurence de 'value' entre it1 et it11
    std::sort(it1, it11)             : trie entre it1 et it11
    std::reverse(it1, it11)          : trie à l'envers entre it1 et it11

    std::replace(it1, it11, value1, value2) : recherche value1 entre it1 et it11, puis le remplace par value2
    std::erase(conteneur, value)     : supprime 'value' de 'conteneur'
    std::remove(it1, it11, value)    : supprime 'value' entre it1 et it11 du conteneur
    std:swap(var1, var2)             : permet d'inverser le contenue de 2 variables/conteneurs

    std::for_each(it1, it11, fonction) : permet de passer en paramètre de fonction, tous les éléments entre it1 et it11
    std::all_of(it1, it11, fonction)  : renvoie Vrai, si tous les éléments entre it1 et it11 valide la fonction
    std::any_of(it1, it11, fonction)  : renvoie Vrai, si au moins 1 élément valide la fonctoin
    std::none_of(it1, it11, fonction) : renvoie Vrai, si aucun élément valide la fonction

    autres : 
    std::stoi : string en int
    std::stod : string en double
*/

bool is_pair(int n)
{
    return n % 2 == 0; // renvoie un boolèen en vérifiant si n est pair
}

void print_elements(int n)
{
    std::cout << n << std::endl;
}

int main()
{
    std::vector<int> vec{11,22,33,44,55};
    std::for_each(std::begin(vec), std::end(vec), print_elements);

    std::cout << std::all_of(std::begin(vec), std::end(vec), is_pair) << std::endl;
    // renvoie vrai, si tous les éléments du début à la fin de 'vec', valide la fonction 'is_pair'

////////////////////////////////////////////////////////////////////////////////////////////////////////

    using namespace std::literals; // permet l'ajout du suffise 's' au chaine de caractère

    std::string s{"Hello World !"s};
    std::string search_term{"World"};

    auto s_begin = std::begin(s);
    auto s_end = std::end(s);
    auto search_begin = std::begin(search_term);
    auto search_end = std::end(search_term);

    if(std::search(s_begin, s_end, search_begin, search_end) != s_end)
    {
        std::cout << search_term << " a ete trouve." << std::endl;
    }

    std::cout << std::count(s_begin, s_end, 'l') << " occurences de 'l' dans " << s << std::endl;
    std::replace(s_begin, s_end, 'l', 'z'); // remplace les 'l' par des 'z' entre le début et la fin de 's'
    std::erase(s, 'z'); // efface tous les 'z' dans 's'
    std::cout << s << std::endl;
    std::cout << "s = " << s << "\nsearch_term = " << search_term << std::endl;
    std::swap(s, search_term); // inverse le contenue de 's' avec celui de 'search_term'
    std::cout << "s = " << s << "\nsearch_term = " << search_term << std::endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<int> vec1{5, 4, 3, 2 ,1};
    std::vector<int> vec2{1, 2 ,3, 4, 5};

    auto begin = std::begin(vec1);
    auto end = std::end(vec1);

    auto result = std::find(begin, end, 3); // std::find() renvoie un itérateur pointant vers l'élément recherché

    if(result != end) // si l'itérateur trouvé ne pointe pas vers la fin (signifie que tout a été parcouru)
    {
        std::cout << "Oui !" << std::endl;
    } 

    for(const auto& element : vec1)
    {
        std::cout << element << std::endl;
    }

    std::sort(begin, end); // trie entre la fin et le début de vec1

    if(std::equal(std::begin(vec1), std::end(vec1), std::begin(vec2), std::end(vec2)))
    // Vérifie l'égalité entre tous le contenu (début à la fin) de 'vec1' et tous le contenu de 'vec2'
    {
        std::cout << "vec1 et vec2 sont égaux." << std::endl;
    }
    else{std::cout << "vec1 et vec2 ne sont pas égaux."<< std::endl;}

    std::fill(std::begin(vec1), std::end(vec1), 0); // remplie le vecteur 'vec' de '0' du début du vecteur à la fin

    for(const auto& element : vec1)
    {
        std::cout << element << std::endl;
    }

    return 0;
}
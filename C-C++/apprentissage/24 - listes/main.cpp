#include <iostream>
#include <string>
#include <list>

/*
    Une liste peut être utile s'il y a beaucoup d'ajout de suppression à faire
*/

int main()
{
    std::list<std::string> li{"saucisse", "arbre", "bateau", "oui"}; // initialise une liste de type string

    std::cout << "Premier : " << li.front() << std::endl; // renvoie le premier élément de la liste
    std::cout << "Dernier : " << li.back() << std::endl; // renvoie le dernier élément de la liste
    std::cout << "Taille : " << li.size() << std::endl; // renvoie la taille de la liste

    li.push_back("castor"); // Ajoute à la fin de la liste 'li', l'élément 'castor'
    std::cout << "Dernier : " << li.back() << std::endl;

    li.push_front("barrage"); // Ajoute au début de la liste 'li', l'élémenet 'barage'
    std::cout << "Premier : " << li.front() << std::endl;

    li.pop_front(); // Supprime le premier élément de la liste
    std::cout << "Premier : " << li.front() << std::endl;

    li.pop_back(); // Supprime le dernier élément de la liste
    std::cout << "Dernier : " << li.back() << std::endl;

    for(const auto& element : li) // Pour chaque élément de la liste 'li'
    {
        std::cout << element << std::endl; // Afficher l'élément de la liste 'li'
    }  

    std::cout << "===============================" << std::endl;
    li.sort(); // Trie de manière ascendante la liste (par ordre alphabétique/chiffre)

    for(const auto& element : li) // Pour chaque élément de la liste 'li'
    {
        std::cout << element << std::endl; // Afficher l'élément de la liste 'li'
    } 

    std::cout << "===============================" << std::endl;
    li.reverse(); // Trie de manière descendante la liste

    for(const auto& element : li) // Pour chaque élément de la liste 'li'
    {
        std::cout << element << std::endl; // Afficher l'élément de la liste 'li'
    } 

    li.clear(); // Supprime tous les éléments de la liste

    if (li.empty()) // si la liste 'li' est vide
    {
        std::cout << "Liste vide." << std::endl; 
    } 

    std::list<std::string> _list{"a", "b", "c", "d", "e"}; // initialise une liste de type 'string'
    for(std::string element : _list)
    {
        std::cout << element << std::endl;
    }

    std::list<std::string>::iterator it = _list.begin(); // pointe l'itérateur 'it' au début de la liste
    it++;
    it++;
    _list.insert(it, "oui"); // place l'élément 'oui' à l'emplacement de l'itérateur : 2 (begin() = 0 et it++ et it++ : it = 2)

    std::cout << "====================" << std::endl;

    for(std::string element : _list)
    {
        std::cout << element << std::endl;
    }

    int position;
    std::string valeurRecherche = "b";
    for (auto it2 = _list.begin(); it2 != _list.end(); it2++) // Pour l'itérateur 'it2 = 0' (début de la liste), ajouter 1 ) 'it2' tant que 'it2' est différent de la fin de la liste
    {
        if(*it2 == valeurRecherche) // le '*' permet d'accèder à la valeur auquel l'itérateur 'it2' pointe
        {
            std::cout << "La position de : " << valeurRecherche << " est : " << position << std::endl; // renvoie la position de 'valeurRecherche' dans la liste '_list'
            break;
        }
        position++; // ajouter 1 à la position à chaque fois que la condition n'est pas vérifier et que la boucle continue
    }
    
    return 0;
}
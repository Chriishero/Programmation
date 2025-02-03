#include <iostream>
#include <list>
#include <algorithm>

int main()
{
    std::list<char> list{'a', 'b', 'c', 'd'};

    char elementRecherche = 'b';

    auto it = std::find(list.begin(), list.end(), elementRecherche); // cherche 'elementRecherche' dans la liste de type char 'list'

    int position = std::distance(list.begin(), it); // calcule la position de 'elementRecherche' à partir de la variable 'it' dans la liste 'list'
    std::cout << elementRecherche << " se trouve à la position : " << position;    


    return 0;
}
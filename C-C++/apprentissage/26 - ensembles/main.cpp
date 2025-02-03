#include <iostream>
#include <unordered_set> // ensemble non ordonnée
#include <set> // ensemble ordonnée

/*
    Ensembles : regroupement de données uniques qui ne peuvent pas être modifié.
    Une valeur ne peut pas exister en doublont.
    Chaque élément aura un hash, qui permettra de les identifier en référence lors de la compilation

    insert(), erase(), clear(), size(), empty(),
    find(), contains()
*/

int main()
{
    std::unordered_set<int> s{1, 4, 55, -7};

    s.insert(9);
    s.insert( {19, 100, 8} ); // {} pour insérer plusieurs valeurs
    s.erase(55);

    if(s.find(4) != std::end(s)) // cherche la valeur 4, équivalent à '.contains(4)'
    // si elle n'est pas trouvé, tout l'ensemble sera parcourue sans la trouver, et  se retourvera donc à la fin : 'std::end(set)'
    {
        std::cout << "Trouvé ! " << std::endl;
    }

    for(const auto& number : s)
    {
        std::cout << number << " ";
    }

    return 0;
}
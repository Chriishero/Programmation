#include <iostream>
#include <string>
#include <unordered_map> // carte associative non-ordonnée
#include <map> // carte associative ordonnée

/*
    Une carte associative est une paire de donnée, qui contient à la fois une clé, et une valeur qui lui est associé,
    même principe que les dictionnaires en python.

    std::unordered_map<key_type, value_type> map{ {key, value} };*

    .at()
    .insert() / .erase()
    .size()
    .empty()
    .contains() : retourne un booléen, si l'élément (clé) est contenu ou non
    .find()
*/

int main()
{
    std::unordered_map<int, std::string> umap{ {3, "Arbre"}, {1, "Maison"}, {2, "Fourchette"} }; // map non-ordonnée
    std::map<int, std::string> omap{ {3, "Biceps"}, {1, "Pectoraux"}, {2, "Quadriceps"} }; // map ordonnée

    std::cout << umap[3] << std::endl; // pour afficher une valeur, il faut entrer sa clé, non pas son indice
    umap[3] = "Forêt"; // idem
    std::cout << umap[3] << std::endl;

    umap[6] = "Patrick Bateman"; // ajoute la nouvelle clé '6' avec sa valeur 'Patrick Bateman'
    umap.insert( { {76, "Louki"}, {8, "Ivan"} } ); // insère de nouvelles clés et leur valeurs.
    // Il est impossible d'insérer une valeur à une clé déjà existante.

    umap.erase(3); // efface la clé '3' et sa valeur

    for(const auto& [key, value] : umap) // si omap était parcourue, les clés et valeurs auraient été trié.
    // for (const auto& pair : umap){ std::cout << pair.first << pair.second; }
    {
        std::cout << key << " > " << value << std::endl;
    }

    if(umap.contains(2))
    {
        std::cout << "Oui" << std::endl;
    }

    else{std::cout << "Non" << std::endl;}

    return 0;
}
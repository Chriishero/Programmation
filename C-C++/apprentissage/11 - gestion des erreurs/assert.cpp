#include <iostream>
#include <string>
#include <cassert> // accès à une macro qui permet de tester une expression, sert uniquement aux erreurs de développeur

void createPlayer(std::string name, int level)
{
    assert(level > 0 && "Le niveau d'un joueur est au minimum de 1."); // si -DNDEBUG est utilisé lors de la compilation, les insertions sont ignorées

    std::cout << "Creation de " << name << ", de niveau " << level << std::endl;
}

int main()
{
    createPlayer("Chris", 0);
    
    return 0;
}
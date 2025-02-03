#include "window.hpp"
#include <iostream>

int main()
{
    Window app{"Mon application graphique"};
    
    std::cout << app.get_title() << std::endl;
    app.set_title("Nouveau titre qui est un peu trop long pour l'interface graphique");
    std::cout << app.get_title() << std::endl; // appelle de l'attribut privé 'title' depuis l'accesseur 'get_title'

    return 0;
}
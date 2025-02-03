#include <iostream>
#include <string>

/*
    Valeur booléenne de vérification :
    Goodbit : bon fonctionnement (1 = true, 0 = false)
    Failbit : erreur à la saisie
    Badbit : erreur de flux, irrécupérable
*/

int main() {

    std::cout << "Entrez un nombre : ";
    int number; 
    std::cin >> number; // pas de flush sur un tampon d'entré 

    std::cin.ignore(255, '\n'); // permet d'ignorer les sauts de ligne et donc de ne pas prendre en compte pour std::cin, name, celui qui occure lorsqu'on appuie sur Entrée pour validé le cin >> number.

    std::cout << "Tapez votre nom complet : ";
    std::string name;
    // std::cin >> name; saisi utilisateur
    std::getline(std::cin, name); // permet de récupérer la ligne entière, ajouter un autre paramètre comme ,':', permet de mettre en place un délimiteur, comme ':' dans ce cas là


    std::cout << "Vous vous appelez : " << name << std::endl;

    std::cout << " Goodbit: " << std::cin.good() << std::endl;
    std::cout << " Failbit: " << std::cin.fail() << std::endl;
    std::cout << " Badbit: " << std::cin.bad() << std::endl;

    return 0;
}
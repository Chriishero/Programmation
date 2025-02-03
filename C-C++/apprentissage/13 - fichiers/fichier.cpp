#include <iostream>
#include <string>
#include <fstream> // plusieurs outils, dont la gestion de fichiers

/*
    std::ios::out, std::ios::in
    std::ios::binary : ouvrir un fichier en mode binaire

    ouvre le fichier à la fin : 
    std::ios::trunc
    std::ios::ate
    std::ios::app // rajoute le text après le text intiale du fichier

    file >> std::ws // supprime les espaces inutiles
*/

int main()
{
    std::ifstream read{"muscles.txt"}; // std::ios::in, lis le fichier muscles.txt
    std::string name{""};

    std::ofstream write{"data.txt", std::ios::app}; // std::ios::out, écris dans le (nouveau) fichier data.txt
    // 'std::ios::app' (append) permet de rajouter le text après le text intiale du fichier

    write << u8"0RIR ! "; // le 'u8' permet d'écrire le fichier en UTF-8 se qui permet de mettre les caractère spéciaux tel que 'é', 'è', 'à', etc

    if(read.is_open())
    {
        std::getline(read >> std::ws, name); // affiche toute la ligne, et std::ws supprime les espaces en début/fin de ligne et le \n
        std::cout << name << std::endl;

        read >> name; // affiche seulement le premier mot de la ligne (2ème vu que la première a été affiché en entière)
        std::cout << name << std::endl;
    }

    read.close(); // fermer manuellement le fichier (C++ le fait automatiquement)

    return 0;
}
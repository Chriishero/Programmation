#include "splitter.hpp"
#include "split_methode.hpp"
#include <iostream>
#include <string>


int main()
{
    bool choice = true;

    std::string pdf_path = "pdf/BAKEMONOGATARI Part 1.pdf";
    Methode split_methode = Methode::personalized;
    std::string save_path = "split/"; // Le chemin de sauvegarde sera par défaut dans le dossier 'split'

    while (choice == true)
    {
        break;
    }

    Splitter s{pdf_path, split_methode, save_path};

    return 0;
}
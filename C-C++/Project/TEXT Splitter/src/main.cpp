#include "../include/splitter.hpp"
#include "../include/split_methode.hpp"
#include <iostream>
#include <fstream>
#include <string>


int main()
{
    int choice = 1;

    std::string txt_path;
    std::string str_split_methode;
    Methode split_methode;
    std::string save_path = "split/"; // Le chemin de sauvegarde sera par défaut dans le dossier 'split'
    int page_interval = 0;


    while (choice == 1)
    {
        std::cout << "Indicate the splitting methode (word/sentence/page/page-interval) : ";
        std::cin >> str_split_methode;

        if (str_split_methode == "word")
        {
            split_methode = Methode::word;
            choice = 2;
        }
        else if (str_split_methode == "sentence")
        {
            split_methode = Methode::sentence;
            choice = 2;
        }
        else if (str_split_methode == "page")
        {
            std::cout << "The pages must be numbered by : 'Page' + 'n'." << std::endl;
            split_methode = Methode::page;
            choice = 2;
        }
        else if (str_split_methode == "page-interval")
        {
            std::cout << "The pages must be numbered by : 'Page' + 'n'." << std::endl;
            split_methode = Methode::page_interval;
            while (choice == 1)
            {
                std::cout << "Choose the page interval (integer) : ";
                std::cin >> page_interval;
                if (page_interval > 0 && page_interval < 10000)
                {
                    choice = 2;
                }
                else
                {
                    std::cout << "Wrong." << std::endl;
                    continue;
                }
            }
        }
        else
        {
            std::cout << "Wrong." << std::endl;
            continue;
        }

        while (choice == 2)
        {
            std::cout << "Enter the path to the file.txt to be separated : ";
            std::cin >> txt_path;

            if (!txt_path.contains(".txt"))
            {
                std::cout << "The file must have the extension .txt." << std::endl;
                continue;
            }
            else{choice = 0; break;}
        }
    }

    Splitter s{txt_path, split_methode, save_path, page_interval};
    s.split_txt();

    return 0;
}

/* CHOISIR L'INTERVAL */
#include "game_init.hpp"
#include "play_game.hpp"
#include "pendu_status.hpp"
#include <iostream>
#include <string>
#include <list>

int main()
{
    std::string word;
    bool help_word;

    while (1)
    {
        std::cout << "Choose a word for the game : ";
        std::cin >> word;
        std::cin.ignore(255, '\n');

        if(word.length() < 3)
        {
            std::cout << "The word must contain at least 3 letters." << std::endl;
            continue;
        }

        else{break;}
    }

    while (1)
    {
        std::cout << "1. First letter only is shown \n2. First and last letter is shown." << std::endl;
        int Nhelp_word;
        std::cin >> Nhelp_word;

        if (Nhelp_word == 1)
        {
            help_word = false;
            break;
        }

        else if (Nhelp_word == 2)
        {
            help_word = true;
            break;
        }
        
        else{std::cout << "Incorrect answer." << std::endl; continue;}
    }
    
    GameInit GI{word, Pendu_status::ongoing};
    PlayGame PG{word, GI.word_letter_list(), Pendu_status::ongoing};

    std::cout << GI.underscore_letter(help_word) << std::endl;
    PG.enter_letter(help_word);

    return 0;
}
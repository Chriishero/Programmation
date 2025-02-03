#include "play_game.hpp"
#include "pendu_status.hpp"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

char test_letter{};
std::list<std::string> underscore_nbr;
bool underscore_nbr_status = false;
std::list<std::string> right_letter_underscore;
bool underscore_status = false;

PlayGame::PlayGame(const std::string& word, const std::list<char>& word_letter_list, Pendu_status status) noexcept : GameInit(word, status), _word_letter_list(word_letter_list)
{
}

std::list<char> PlayGame::right_word_letter_list(bool help_word) const noexcept
{       
    std::list<char> _right_word_letter_list{GameInit::word_letter_list()};

    if(help_word == false)
    {
        _right_word_letter_list.pop_front();
    }

    else
    {
        _right_word_letter_list.pop_front();
        _right_word_letter_list.pop_back();
    }
    
    return _right_word_letter_list;
}

void PlayGame::wrong_letter(int& fail_number) noexcept
{
    switch (fail_number)
    {
    case 1:
        std::cout << "\n\n\n\n\n" << "_|_________" << std::endl;
        break;
    case 2:
        std::cout << "\n |\n |\n |\n |\n" << "_|_________" << std::endl;
        break;
    case 3:
        std::cout << "\n |/\n |\n |\n |\n" << "_|_________" << std::endl;
        break;
    case 4:
        std::cout << "\n_________\n |/\n |\n |\n |\n" << "_|_________" << std::endl;
        break;
    case 5:
        std::cout << "\n_________\n |/     O\n |\n |\n |\n" << "_|_________" << std::endl;
        break;
    case 6:
        std::cout << "\n_________\n |/     O\n |      |\n |\n |\n" << "_|_________" << std::endl;
        break;
    case 7:
        std::cout << "\n_________\n |/     O\n |      |-\n |\n |\n" << "_|_________" << std::endl;
        break;
    case 8:
        std::cout << "\n_________\n |/     O\n |     -|-\n |\n |\n" << "_|_________" << std::endl;
        break;
    case 9:
        std::cout << "\n_________\n |/     O\n |     -|-\n |      |\n |\n" << "_|_________" << std::endl;
        break;
    case 10:
        std::cout << "\n_________\n |/     O\n |     -|-\n |      |\\ \n |\n" << "_|_________" << std::endl;
        GameInit::set_status(Pendu_status::fail);
        break;
    }
}

void PlayGame::show_right_letter(const std::list<char>& word_letter_list, bool help_word) const noexcept
{
    std::string first_letter{GameInit::word_letter_list().front()};
    std::string last_letter{GameInit::word_letter_list().back()};

    auto it = std::find(word_letter_list.begin(), word_letter_list.end(), test_letter);
    int position = std::distance(word_letter_list.begin(), it);

    auto it_underscore = underscore_nbr.begin();

    if (help_word == false)
    {
        if(underscore_nbr_status == false)
        {
            for (auto i = 0; i < GameInit::lenght_word() - 1; i++)
            {
                underscore_nbr.push_front("_");
            }
            position += 1;
        }
        underscore_nbr_status = true;

        std::advance(it_underscore, position);
        *it_underscore = test_letter;

        right_letter_underscore = underscore_nbr;
        right_letter_underscore.push_front(first_letter);

        for(auto element : right_letter_underscore)
        {
            std::cout << element;
        }
        std::cout << std::endl;
    }

    else
    {
        if(underscore_nbr_status == false)
        {
            for (auto i = 0; i < GameInit::lenght_word() - 2; i++)
            {
                underscore_nbr.push_front("_");
            }
            position += 1;
        }
        underscore_nbr_status = true;

        std::advance(it_underscore, position);
        *it_underscore = test_letter;

        right_letter_underscore = underscore_nbr;
        right_letter_underscore.push_front(first_letter);
        right_letter_underscore.push_back(last_letter);

        for(auto element : right_letter_underscore)
        {
            std::cout << element;
        }
        std::cout << std::endl;

    }
}

void PlayGame::enter_letter(bool help_word) noexcept
{
    int fail_number{};

    while(GameInit::get_status() == Pendu_status::ongoing)
    {       
        bool _wrong_letter = true;
        std::cout << "Enter a letter : ";
        std::cin >> test_letter;

        for(char letter : right_word_letter_list(help_word))
        {
            if(test_letter == letter)
            {
                _wrong_letter = false;
                std::cout << test_letter << " is a right letter." << std::endl;
            }
        }

        if (_wrong_letter == false)
        {
            show_right_letter(right_word_letter_list(help_word), help_word);
            auto find_underscore = std::find(right_letter_underscore.begin(), right_letter_underscore.end(), "_");
            if(*find_underscore != "_")
            {
                GameInit::set_status(Pendu_status::win);
                break;
            }
            continue;
        }

        else if (_wrong_letter == true)
        {
            fail_number++;
            wrong_letter(fail_number);
            continue;
        }
    }

    if (GameInit::get_status() == Pendu_status::win)
    {
        std::cout << "You won, the word was : " << GameInit::get_word() << std::endl;
    }
    
    else if (GameInit::get_status() == Pendu_status::fail)
    {
        std::cout << "You failed, the word was : " << GameInit::get_word() << std::endl;
    }
    
}
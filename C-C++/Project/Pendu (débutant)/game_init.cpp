#include "game_init.hpp"
#include <iostream>
#include <string>
#include <list>

GameInit::GameInit(const std::string& word, Pendu_status status) noexcept : _word(word), _status(status)
{
    _status = Pendu_status::ongoing;
}

int GameInit::lenght_word() const noexcept
{
    return _word.length();
}

std::string GameInit::get_word() const noexcept
{
    return _word;
}

std::list<char> GameInit::word_letter_list() const noexcept
{
    std::list<char> _word_letter_list{};

    for (char letter : _word)
    {
        _word_letter_list.push_back(letter);
    }

    return _word_letter_list;
    
}

std::string GameInit::underscore_letter(bool help_word) const noexcept
{
    std::string _underscore_letter;
    std::string underscore_nbr;
    std::string first_letter{word_letter_list().front()};
    std::string last_letter{word_letter_list().back()};

    if (help_word == false)
    {
        for (auto i = 0; i < GameInit::lenght_word() - 1; i++)
        {
            underscore_nbr += "_";
        }
        _underscore_letter = first_letter + underscore_nbr;
    }

    else
    {
        for (auto i = 0; i < GameInit::lenght_word() - 2; i++)
        {
            underscore_nbr += "_";
        }

        _underscore_letter = first_letter + underscore_nbr + last_letter;
    }
    
    return _underscore_letter;
        
}

Pendu_status GameInit::get_status() const noexcept
{
    return _status;
}

void GameInit::set_status(Pendu_status status)
{
    _status = status;
}


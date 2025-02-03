#include "../include/gameinit.hpp"
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> area;
int player_position;
bool already_called = false;

GameInit::GameInit(int area_height, int area_width, int starting_position) noexcept : _area_height(area_height), _area_width(area_width), _starting_position(starting_position)
{}

void GameInit::init_area() const noexcept
{
    auto i = 0;

    if (already_called == false) // tout le code du bloc conditionnelle ne s'effectura qu'une fois, à la première utilisation de la fonction
    {
        for (auto i = 0; i < _area_width*_area_width; i++)
        { 
            if (i < _area_width + 1 || i > _area_width * (_area_height-1) - 2) 
            {
                area.push_back("O "); // tout première et dernière, côté gauche deuxième , côté droit avant-dernière
            }

            else if(i != _area_width/2 && i % _area_width == 0) // si tous les _area_width * n + 1, avec n>1 et <_area_height-1
            {
                area.push_back("O "); // tous le côté gauche, sauf deuxième ligne, et dernière
            }

            else if((i-_area_width+1) % _area_width == 0) // si tous les _area_width * n avec n>1
            {
                area.push_back("O "); // tous le côté droit, sauf 1er ligne, avant dernière, et dernière
            }

            else
            {
                area.push_back("  ");
            }
        }

        if (_starting_position <= _area_width - 1 && _starting_position > 0 && area[_starting_position + _area_width] != "O ") // si '_starting_position' appartient à la première ligne
        {
            player_position = _starting_position + _area_width;
            area[player_position] = "* "; 
        }

        for (auto i = 1; i < _area_height-2; i++) // pour la zone accessible d'une colonne
        {
            if (_starting_position > (_area_height - 2) * i && _starting_position <= (_area_height - 2) * i + _area_height - 2) // si '_starting_position' se trouve entre la valeur mini et max de la ligne de la colonne 'i'
            {
                player_position = _starting_position + _area_width + 2 * i;
                area[player_position] = "* "; // ajouter '_area_width' plus 2 fois le numéro de la colonne
                break;
            } 
        }
        already_called = true;
    }

    already_called = true;
    
    for(const auto& element : area)
    {
        i++;
        std::cout << element;
        if (i % _area_width == 0)
        {
            std::cout << std::endl;
        }
        
    }
}  

void GameInit::set_player_position(std::string button) const noexcept
{
    if(button == "U" || button == "Up")
    {
        if (area[player_position - _area_width] != "O ")
        {
            area[player_position] = "  ";
            area[player_position - _area_width] = "* ";
            player_position -= _area_width;
            init_area();
        }
        else
        {
            std::cout << "You can't move to a wall." << std::endl;
        }
    }

    else if(button == "D" || button == "Down")
    {
        if (area[player_position + _area_width] != "O ")
        {
            area[player_position] = "  ";
            area[player_position + _area_width] = "* ";
            player_position += _area_width;
            init_area();
        }
        else
        {
            std::cout << "You can't move to a wall." << std::endl;
        }
    }

    else if(button == "L" || button == "Left")
    {
        if (area[player_position - 1] != "O ")
        {
            area[player_position] = "  ";
            area[player_position - 1] = "* ";
            player_position--;
            init_area();
        }
        else
        {
            std::cout << "You can't move to a wall." << std::endl;
        }
    }
    
    else if(button == "R" || button == "Right")
    {
        if (area[player_position + 1] != "O ")
        {
            area[player_position] = "  ";
            area[player_position + 1] = "* ";
            player_position++;
            init_area();
        }
        else
        {
            std::cout << "You can't move to a wall." << std::endl;
        }
    }
}

#include "include\gameinit.hpp"
#include "include\game_status.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cstdlib> // bibliothèque qui inclue la génération aléatoire avec rand()

std::vector<std::string> starting_area{};
std::vector<std::string> mine_area{};

std::vector<int> point_per_player{};

bool is_starting_area = false;
bool mine_here = false;
int number_mine = 0;
int i{0};

std::string string_number_mine{std::to_string(number_mine) + " "};
Game_status status_;

GameInit::GameInit(int n_player, const int area_size, const int area_width, const int area_height, Game_status status, int difficulty) noexcept : _n_player(n_player), _area_size(area_size), _area_width(area_width), _area_height(area_height),
 _status(status), _difficulty(difficulty)
{   
    _status = Game_status::ongoing;  
}

Game_status GameInit::get_status() const noexcept
{
    return status_;
}

void GameInit::set_status(Game_status status)
{
    _status = status;
}

void GameInit::set_base_point(int n_player) const noexcept
{
    for (auto i = 0; i < n_player; i++)
    {
        point_per_player.push_back(0);
    }    
}

void GameInit::show_point_array() const noexcept
{
    for (const auto& n : point_per_player)
    {
        std::cout << n << std::endl;
    }
}

void GameInit::set_point(int player) const noexcept
{
    point_per_player[player-1] += number_mine + 1;
}

int GameInit::get_point(int player) const noexcept 
{
    int point = point_per_player[player-1];
    return point;
}

void GameInit::point_to_zero(int player) const noexcept
{
    point_per_player[player-1] = 0;
}

void GameInit::generate_mine() const noexcept
{
    srand(time(NULL)); // Le tirage aléatoire sera différent à chaque lancement

    switch (_difficulty)
    {
    case 1:
        for (auto i = 0; i < _area_size/8; i++)
        {
            int random = rand()%_area_size-1 +0; // Génére un nombre aléatoire entre _area_size-1 et 0
            //std::cout << random << std::endl;
            mine_area[random] = "M ";
        }
        
        break;
    
    case 2:
        for (auto i = 0; i < _area_size/6; i++)
        {
            int random = rand()%_area_size-1 +0; // Génére un nombre aléatoire entre _area_size-1 et 0 
            //std::cout << random << std::endl;
            mine_area[random] = "M ";
        }
        break;

    case 3:
        for (auto i = 0; i < _area_size/5; i++)
        {
            int random = rand()%_area_size-1 +0; // Génére un nombre aléatoire entre _area_size-1 et 0
            //std::cout << random << std::endl;
            mine_area[random] = "M ";
        }
        break;

    case 4:
        for (auto i = 0; i < _area_size/3; i++)
        {
            int random = rand()%_area_size-1 +0; // Génére un nombre aléatoire entre _area_size-1 et 0
            //std::cout << random << std::endl;
            mine_area[random] = "M ";
        }
        break;
    }
}

void GameInit::check_mine_around(int selected_case, int player) const noexcept
{
    if (mine_area[selected_case] == "M ")
    {
        status_ = Game_status::fail;
    }

   if((selected_case - 1)%_area_width == 0) // vérifie si selected_case - 1 est un multiple de _area_width, avec l'opérateur modulo, si l'opération = 0, alors c'est un multiple
    {
        if (mine_area[selected_case - 1] == "M ") // si selected_case - 1 est un multiple de _area_width, alors
        {
            number_mine++;
            string_number_mine = std::to_string(number_mine) + " ";
            starting_area[selected_case] = string_number_mine;
            mine_area[selected_case] = string_number_mine;
        }
    }
    else
    {
        if (mine_area[selected_case - 1] == "M ") // si selected_case - 1 est un multiple de _area_width, alors
        {
            number_mine++;
            string_number_mine = std::to_string(number_mine) + " ";
            starting_area[selected_case] = string_number_mine;
            mine_area[selected_case] = string_number_mine;
        }  
    }

    if((selected_case + 1)%_area_width != 0) // vérifie si selected_case + 1 N'est PAS un multiple de _area_width, avec l'opérateur modulo, si l'opération = 0, alors c'est un multiple, si !=, alors non
    {
        if (mine_area[selected_case + 1] == "M ") // ici
        {
            number_mine++;
            string_number_mine = std::to_string(number_mine) + " ";
            starting_area[selected_case] = string_number_mine;
            mine_area[selected_case] = string_number_mine;
        }
    }
    else
    {
        if (mine_area[selected_case + 1] == "M ") // si selected_case - 1 est un multiple de _area_width, alors
        {
            number_mine++;
            string_number_mine = std::to_string(number_mine) + " ";
            starting_area[selected_case] = string_number_mine;
            mine_area[selected_case] = string_number_mine;
        }  
    }

    if (mine_area[selected_case - _area_width] == "M ")
    {
        number_mine++;
        string_number_mine = std::to_string(number_mine) + " ";
        starting_area[selected_case] = string_number_mine;
        mine_area[selected_case] = string_number_mine;
    }


    if((selected_case - _area_width - 1) % _area_width == 0)
    {
        if (mine_area[selected_case - _area_width - 1] == "M ")
        {
            number_mine++;
            string_number_mine = std::to_string(number_mine) + " ";
            starting_area[selected_case] = string_number_mine;
            mine_area[selected_case] = string_number_mine;
        }
    }


    if((selected_case - _area_width + 1) % _area_width != 0)
    {
        if (mine_area[selected_case - _area_width + 1] == "M ")
        {
            number_mine++;
            string_number_mine = std::to_string(number_mine) + " ";
            starting_area[selected_case] = string_number_mine;
            mine_area[selected_case] = string_number_mine;
        }
    }

    if (mine_area[selected_case + _area_width] == "M ")
    {
        number_mine++;
        string_number_mine = std::to_string(number_mine) + " ";
        starting_area[selected_case] = string_number_mine;
        mine_area[selected_case] = string_number_mine;
    }

    if((selected_case + _area_width - 1) % _area_width == 0) // si selected_case + _area_width - 1 est un multiple de _area_width, alors
    {
        if (mine_area[selected_case + _area_width - 1] == "M ")
        {
            number_mine++;
            string_number_mine = std::to_string(number_mine) + " ";
            starting_area[selected_case] = string_number_mine;
            mine_area[selected_case] = string_number_mine;
        }
    }

    if((selected_case + _area_width + 1) % _area_width != 0)
    {
        if (mine_area[selected_case + _area_width + 1] == "M ") 
        {
            number_mine++;
            string_number_mine = std::to_string(number_mine) + " ";
            starting_area[selected_case] = string_number_mine;
            mine_area[selected_case] = string_number_mine;
        }
    }

    if (status_ == Game_status::fail)
    {
       starting_area[selected_case] = "M ";
    }

    else
    {
        string_number_mine = std::to_string(number_mine) + " ";
        starting_area[selected_case] = string_number_mine;
        mine_area[selected_case] = string_number_mine;
    }
    
    set_point(player);
}

void GameInit::generate_area() const noexcept
{
    if (is_starting_area == false)
    {
        for (int i = 1; i < _area_width; i++)
        {
            std::cout << i << " ";
        }
    
        std::cout << std::endl;

        for (int i = 0; i < _area_height; i++)
        {
            for (auto i = 0; i < _area_width; i++)
            {
                starting_area.push_back("* ");
            }
        }
    }
    is_starting_area = true;

    for(const auto& element : starting_area)
    {
        i++;
        std::cout << element; 
        if (i == _area_width)
        {
            std::cout << std::endl;
            i = 0;
        } 
    }
    mine_area = starting_area;
}

void GameInit::new_area(int selected_case, int player) const noexcept
{
    number_mine = 0;
    status_ = Game_status::ongoing;
    check_mine_around(selected_case, player); 

    if (get_point(player) > 1)
        {
            std::cout << "Player " << player << " : " << get_point(player) << " points." << std::endl;
        }
        
    else if (get_point(player) <= 1)
        {
            std::cout << "Player " << player << " : " << get_point(player) << " point." << std::endl;
        }

    for(const auto& element : starting_area)
    {
        i++;
        std::cout << element; 
        if (i == _area_width)
        {
            std::cout << std::endl;
            i = 0;
        } 
    }
}

void GameInit::show_mine_area() const noexcept
{
    for(const auto& element : mine_area)
    {
        i++;
        std::cout << element; 
        if (i == _area_width)
        {
            std::cout << std::endl;
            i = 0;
        } 
    }
}

bool GameInit::check_win_solo() const noexcept
{
    bool win = true;

    for (const auto& element : mine_area)
    {
        if (element == "* ")
        {
            win = false;
        }
        
    }

    return win;
}

bool GameInit::check_win_multiplayer_point(bool check_default_win) const noexcept
{
    bool check = 1;

    if (check_default_win == 0)
    {
        for (const auto& element : mine_area)
        {
            if (element == "* ")
            {
                check = 0;
            }
        }
    }
    
    
    return check;
}

void GameInit::convert_selected_case(std::array<int, 2>& case_coordinate, int& selected_case) const noexcept
{
    case_coordinate[0]--;
    case_coordinate[1]--;
    
    selected_case = case_coordinate[0] + _area_width * case_coordinate[1]; 
}
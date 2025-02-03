#include "include/gameinit.hpp"
#include "include/player.hpp"
#include "include/game_status.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <list>

int main()
{

int n_player;
int width;
int height;

std::array<int, 2> case_coordinate{2,2};
int height_coordinate;
int width_coordinate;
int selected_case = 1;

bool choice{true};
bool win = false;
std::vector<int> already_selected_case;
bool already_selected = false;
int difficulty;

std::vector<std::string> exit;
    while (choice == true)
    {
        std::cout << "Number of player(s) : ";
        std::cin >> n_player;

        if (n_player < 1)
        {
            std::cout << "The minimum number of player is 1." << std::endl;
            continue;
        }

        else
        {
            while (choice == true)
            {
                std::cout << "Width of the area (min 5): ";
                std::cin >> width;

                if (width < 5)
                {
                    std::cout << "The minimum width is 5." << std::endl;
                    continue;
                }

                else
                {
                    while (choice == true)
                    {
                        std::cout << "Height of the area (min 5): ";
                        std::cin >> height;

                        if (height < 5)
                        {
                            std::cout << "The minimum height is 5." << std::endl;
                            continue;
                        }

                        else{
                            while (choice == true)
                            {
                                std::cout << "1. Easy (1/8 of mine)\n2. Normal (1/6) \n3. Hard (1/5)\n4. Impossible (1/3)\nChoose a difficulty (1-4) : ";
                                std::cin >> difficulty;
                                
                                if (difficulty > 4 || difficulty < 1)
                                {
                                    std::cout << "Choose a number between 1 and 4" << std::endl;
                                    continue;
                                }

                                else{choice = false;}
                                
                            }
                            
                        }
                    }
                }
            }
        }
    }

    GameInit GI{n_player, width*height, width, height, Game_status::ongoing, difficulty};
    Player p{};

    GI.generate_area();
    GI.generate_mine();

    p.set_player_array(n_player);
    GI.set_base_point(p.get_player_array().size());
    //GI.show_point_array();
    //std::cout << "---------------------" << std::endl;
    //GI.show_mine_area();
    //p.show_player_array();

    while (win != true)
    {
        for (const auto& player : p.get_player_array())
        {
            if(player != 0)
            {
                if (p.get_player_array().size() > 1)
                {
                    if (p.check_win_multiplayer_default() == 1)
                    {
                        GI.set_status(Game_status::end);
                        std::cout << "Player " << player << " wins." << std::endl;
                        GI.show_mine_area();
                        win = true;
                        break;
                    }

                    else if (GI.check_win_multiplayer_point(p.check_win_multiplayer_default()) == 1)
                    {
                        std::cout << std::endl;
                        GI.show_mine_area();
                        std::cout << std::endl;

                        for (const auto& p : p.get_player_array())
                        {
                            if(p != 0)
                            {
                                std::cout << "Player " << p << " : " << GI.get_point(p) << std::endl;
                            }   
                        }

                        win = true;
                        break;
                    }
                }

                else
                {
                    if (GI.check_win_solo() == true)
                    {
                        GI.set_status(Game_status::end);
                        std::cout << "You win." << std::endl;
                        GI.show_mine_area();
                        win = true;
                        break;
                    }
                }

                while (1)
                {
                    std::cout << "Player " << player << ", select a case (x,y): ";
                    std::cin >> width_coordinate;
                    std::cin.ignore(1, ',');
                    std::cin >> height_coordinate;

                    case_coordinate[0] = width_coordinate;
                    case_coordinate[1] = height_coordinate;
                    GI.convert_selected_case(case_coordinate, selected_case);

                    for (const auto& element : already_selected_case)
                    { 
                        if (element == selected_case)
                        {
                            std::cout << "This case has already been selected." << std::endl;
                            already_selected = true;
                        }
                    }

                    
                    if (width_coordinate > width || width_coordinate < 1)
                    {
                        std::cout << "x (line) must be between 1 and " << width << std::endl;
                        continue;
                    }

                    if (height_coordinate > height || height_coordinate < 1)
                    {
                        std::cout << "y (column) must be between 1 and " << height << std::endl;
                        continue;
                    }
                    
                    else
                    {    
                        if (already_selected == true)
                        {
                            GI.set_status(Game_status::ongoing);
                            already_selected = false;
                            continue;
                        }
                        
                        GI.new_area(selected_case, player);
                        //std::cout << "--------" << std::endl;
                        //GI.show_mine_area();

                        //GI.show_point_array();
                        break;
                    }
                }
                
                if (GI.get_status() == Game_status::fail)
                {
                    std::cout << "Player " << player << " failed." << std::endl;
                    if (p.get_player_array().size() == 1)
                    {
                        GI.show_mine_area();
                        win = true;
                        if (win == true)
                        {
                            std::string exitS;
                            std::cout << "Exit... ";
                            std::cin >> exitS;
                            exit.push_back(exitS);
                            win = true;
                            break;
                        }
                    }
                    GI.point_to_zero(player);
                    p.delete_player(player);
                }

                already_selected_case.push_back(selected_case);
                //p.show_player_array();
            }
        }
    }
    return 0;
}

// RENDRE L'ENTRÉ DES CASES PLUS SIMPLE

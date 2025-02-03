#include "../include/gameinit.hpp"
#include "../include/game_status.hpp"
#include <iostream>
#include <vector>
#include <string>

int main()
{
    int width = 10;
    int height = 10;
    int starting_position = (width-2) * (height-2) + 1;

    GameStatus status = GameStatus::ongoing;

    std::string button;

    while(starting_position > (width-2) * (height-2))
    {
        std::cout << "Choose a departure position (1 - " << (width-2) * (height-2) << ") : ";
        std::cin >> starting_position;
    }

    GameInit GI{height, width, starting_position};
    GI.init_area();

    while (status == GameStatus::ongoing)
    {
        std::cout << "Move the player (Up-Down-Left-Right) : ";
        std::cin >> button;
        if (button == "Up" || button == "U" || button == "Down" || button == "D" || button == "Left" || button == "L" || button == "Right" || button == "R")
        {
            GI.set_player_position(button);
        }
        else{continue;}
    }

    return 0;
}
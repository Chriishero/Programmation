#include "../include/gameinit.hpp"
#include "../include/player.hpp"
#include "../include/enum.hpp"
#include <iostream>
#include <string>
#include <array>

int main()
{
    char exit;
    std::string piece_case;
    std::string target_case;

    GameInit GI{};
    GI.generate_board();
    Player p1{Mode::duo, PlayerStatus::ongoing, "w"};
    Player p2{Mode::duo, PlayerStatus::ongoing, "b"};

    std::array<Player, 2> p_array{p1, p2};
    
    while (1)
    {
        if (p2.get_status() == PlayerStatus::checkmate || p2.get_status() == PlayerStatus::draw || p2.get_status() == PlayerStatus::stalemate)
        {
            break;
        }

        while (1)
        {
            std::cout << "White, write your move (piece_case,target_case) : ";
            std::getline(std::cin, piece_case, ',');
            std::getline(std::cin, target_case);
            if (p1.move_piece(false, piece_case, target_case) == true) 
            {
                p2.generate_board(); 
                break;
            }
            else if (p1.get_status() == PlayerStatus::checkmate || p1.get_status() == PlayerStatus::draw || p1.get_status() == PlayerStatus::stalemate)
            {
                break;
            }
            else{continue;}
        }
        if (p1.get_status() == PlayerStatus::checkmate || p1.get_status() == PlayerStatus::draw || p1.get_status() == PlayerStatus::stalemate)
        {
            break;
        }
        while (1)
        {
            std::cout << "Black, write your move (piece_case,target_case) : ";
            std::getline(std::cin, piece_case, ',');
            std::getline(std::cin, target_case);
            if (p2.move_piece(false, piece_case, target_case) == true) 
            {
                p2.generate_board(); 
                break;
            }
            else if (p2.get_status() == PlayerStatus::checkmate || p2.get_status() == PlayerStatus::draw || p2.get_status() == PlayerStatus::stalemate)
            {
                break;
            }
            else{continue;}
        }
    }

    std::cout << "Type something to exit..." << std::endl;
    std::cin >> exit;
    

    return 0;
}
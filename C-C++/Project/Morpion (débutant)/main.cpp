#include <iostream>

char case1_state{'*'};
char case2_state{'*'};
char case3_state{'*'};
char case4_state{'*'};
char case5_state{'*'};
char case6_state{'*'};
char case7_state{'*'};
char case8_state{'*'};
char case9_state{'*'};

bool game_state{0};
bool case_taken{0};


void display_game()
{
    std::cout << case1_state << case2_state << case3_state << "\n" << case4_state << case5_state << case6_state << "\n" << case7_state << case8_state << case9_state << std::endl;
}

void place(int position, char player)
{
    switch (position)
    {
        case 1:
            if (case1_state != '*')
            {
                case_taken = 1;
                std::cout << "This case is already taken." << std::endl;
                break;
            }
            else 
            {
                case_taken = 0;
                case1_state = player;
                display_game();
                break;
            }
        case 2:
            if (case2_state != '*')
            {
                case_taken = 1;
                std::cout << "This case is already taken." << std::endl;
                break;
            }
            else 
            {
                case_taken = 0;
                case2_state = player;
                display_game();
                break;
            }
        case 3:
            if (case3_state != '*')
            {
                case_taken = 1;
                std::cout << "This case is already taken." << std::endl;
                break;
            }
            else 
            {
                case_taken = 0;
                case3_state = player;
                display_game();
                break;
            }
        case 4:
            if (case4_state != '*')
            {
                case_taken = 1;
                std::cout << "This case is already taken." << std::endl;
                break;
            }
            else 
            {
                case_taken = 0;
                case4_state = player;
                display_game();
                break;
            }
        case 5:
            if (case5_state != '*')
            {
                case_taken = 1;
                std::cout << "This case is already taken." << std::endl;
                break;
            }
            else 
            {
                case_taken = 0;
                case5_state = player;
                display_game();
                break;
            }
        case 6:
            if (case6_state != '*')
            {
                case_taken = 1;
                std::cout << "This case is already taken." << std::endl;
                break;
            }
            else 
            {
                case_taken = 0;
                case6_state = player;
                display_game();
                break;
            }
        case 7:
            if (case7_state != '*')
            {
                case_taken = 1;
                std::cout << "This case is already taken." << std::endl;
                break;
            }
            else 
            {
                case_taken = 0;
                case7_state = player;
                display_game();
                break;
            }
        case 8:
            if (case8_state != '*')
            {
                case_taken = 1;
                std::cout << "This case is already taken." << std::endl;
                break;
            }
            else 
            {
                case_taken = 0;
                case8_state = player;
                display_game();
                break;
            }
        case 9:
            if (case9_state != '*')
            {
                case_taken = 1;
                std::cout << "This case is already taken." << std::endl;
                break;
            }
            else 
            {
                case_taken = 0;
                case9_state = player;
                display_game();
                break;
            }
    }
}

void check_game_state(char player)
{
    if (case1_state == player && case2_state == player && case3_state == player)
    {
        std::cout << "Player " << player << " wins." << std::endl;
        game_state = 1;
    }

    else if (case1_state == player && case4_state == player && case7_state == player)
    {
        std::cout << "Player " << player << " wins." << std::endl;
        game_state = 1;
    }
    else if (case1_state == player && case5_state == player && case9_state == player)
    {
        std::cout << "Player " << player << " wins." << std::endl;
        game_state = 1;
    }
    else if (case2_state == player && case5_state == player && case8_state == player)
    {
        std::cout << "Player " << player << " wins." << std::endl;
        game_state = 1;
    }
    else if (case3_state == player && case6_state == player && case9_state == player)
    {
        std::cout << "Player " << player << " wins." << std::endl;
        game_state = 1;
    }
    else if (case3_state == player && case5_state == player && case7_state == player)
    {
        std::cout << "Player " << player << " wins." << std::endl;
        game_state = 1;
    }
    else if (case4_state == player && case5_state == player && case6_state == player)
    {
        std::cout << "Player " << player << " wins." << std::endl;
        game_state = 1;
    }
    else if (case7_state == player && case8_state == player && case9_state == player)
    {
        std::cout << "Player " << player << " wins." << std::endl;
        game_state = 1;
    }
    else if (case1_state != '*' && case2_state != '*' && case3_state != '*' && case4_state != '*' && case5_state != '*' && case6_state != '*' && case7_state != '*' && case8_state != '*' && case9_state != '*')
    {
        std::cout << "Ex aequo." << std::endl;
        game_state = 1;
    }
}

int main()
{
    char player1{'x'};
    bool player1_state{1};
    char player2{'O'};
    bool player2_state{0};
    int position;

    std::cout << "Player x : x\n" << "Player O : O" << std::endl;
    display_game();
    while(game_state == 0)
    {
        if (player1_state == 1)
        {
            check_game_state(player1);
            std::cout << "Player x, choose a position between 1-9 : ";
            std::cin >> position;
            place(position, player1);
            if(case_taken == 1)
                {
                    continue;
                }
            check_game_state(player1);
            if (position > 9 || position < 1)
                {
                    continue;
                }
            else
            {
                player1_state = 0;
                player2_state = 1;
                continue;
            }
        }

        else if (player2_state == 1)
        {
            check_game_state(player2);
            std::cout << "Player O, choose a position between 1-9 : ";
            std::cin >> position;
            place(position, player2);
            check_game_state(player2);
            if(case_taken == 1)
                {
                    continue;
                }
            if (position > 9 || position < 1)
                {
                    continue;
                }
            else
            {
                player1_state = 1;
                player2_state = 0;
                continue;
            }
        } 
        
    }
    return 0;
}
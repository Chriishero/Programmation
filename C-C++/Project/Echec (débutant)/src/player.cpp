#include "../include/player.hpp"
#include "../include/gameinit.hpp"
#include <iostream>
#include <string>
#include <set>
#include <map>

std::map<std::string, std::string>* PTR_board = nullptr;
std::map<int, std::string> all_move;
std::map<int, std::string> all_w_move;
std::map<int, std::string> all_b_move;
std::set<std::string> case_check;
std::set<std::string> case_king;
std::set<std::string> case_between_king;
std::string check_responsable;
int n_w_repetition = 0;
int n_b_repetition = 0;
int n_move_w = 0;
int n_move_b = 0;
int n_movable_piece = 0;
int n_total_move = 0;
int n_total_w_move = 0;
int n_total_b_move = 0;
int n_no_capture_or_pawn = 0;
bool check_enemies = false;
bool same_color_global = true;
bool draw = false;
bool claimed_draw = false;


Player::Player(Mode mode, PlayerStatus status, std::string color_player) noexcept : GameInit(), _mode(mode), _status(status), _color_player(color_player)
{
    PTR_board = &piece_initial_board_content;
}

void Player::set_status(PlayerStatus status) noexcept
{
    this->_status = status;
}

PlayerStatus Player::get_status() const noexcept
{
    return this->_status;
}

std::string Player::get_color_player() const noexcept
{
    return this->_color_player;
}

void Player::check_status(bool same_color) noexcept
{
    n_movable_piece = 0;
    if (same_color == true)
    {
        for (const auto& [key, value] : (*PTR_board))// les () de '(*PTR_board)[key]' permette d'utiliser la clé pour accèder à la valeur cible depuis le pointeur
        // cette boucle est pour 'piece_case'
        {
            if (value.contains(_color_player)) // donc doit contenir '_color_player'
            {
                for (const auto& [key_target, value_target] : (*PTR_board)) 
                // cette boucle est pour 'target_case'
                {
                    if (!value_target.contains(_color_player)) // ne doit donc pas contenir '_color_player'
                    {
                        move_piece(true, key, key_target); 
                    }
                }
            }
        }
    }
    else
    {
        for (const auto& [key, value] : (*PTR_board))// les () de '(*PTR_board)[key]' permette d'utiliser la clé pour accèder à la valeur cible depuis le pointeur
        // cette boucle est pour 'piece_case'
        {
            same_color_global = true;
            if (!value.contains(_color_player)) // donc ne doit pas contenir '_color_player'
            {
                for (const auto& [key_target, value_target] : (*PTR_board)) 
                // cette boucle est pour 'target_case'
                {
                    if (value_target.contains(_color_player)) // doit contenir '_color_player'
                    {
                        move_piece(true, key, key_target); 
                        same_color_global = false;
                    }
                }
            }
        }
    }
    
}

bool Player::checkmate_stalemate_status() noexcept
{
    for (const auto& [key, value] : (*PTR_board))
    // cette boucle est pour 'piece_case'
    {
        if (value.contains(_color_player) && value.contains("K")) // donc doit contenir '_color_player'
        {
            for (const auto& [key_target, value_target] : (*PTR_board)) 
            // cette boucle est pour 'target_case'
            {
                if (!value_target.contains(_color_player))
                {
                    move_piece(true, key, key_target); 
                }
            }
        }
        if (value.contains(_color_player) && !value.contains("K")) // donc doit contenir '_color_player'
        {
            move_piece(true, key, check_responsable); 
        }
    }

    for (const auto& e : case_king) // vérifie si la case où peut se déplacer le roi, existe
    {
        bool yes_or_no = false;
        for (const auto& [key, value] : _initial_board_content)
        {
            if (e == key)
            {
                yes_or_no = true;
            } 
        }
        if (yes_or_no == false) // si, non
        {
            case_king.erase(e); // elle est supprimé
        }
    }

    if ((*PTR_board)[check_responsable].contains("w"))
    {
        for (const auto& [key, value] : (*PTR_board)) 
        {
            if (value == "wK")
            {
                move_piece(true, check_responsable, key);
            }
        }
    }
    else if ((*PTR_board)[check_responsable].contains("b"))
    {
        for (const auto& [key, value] : (*PTR_board)) 
        {
            if (value == "bK")
            {
                move_piece(true, check_responsable, key);
            }
        }
    }
    

    if (case_king.empty())
    {
        return true;
    }
    else
    {    
        for (const auto& e : case_king)
        {
            std::cout << e << " ";
        }
        std::cout << std::endl;
        for(const auto& e : case_between_king)
        {
            std::cout << e << " ";
        }
        std::cout << std::endl;

        case_king.clear();
        return false;
    }
    
}

bool Player::dead_position_status() noexcept
{
    std::set<std::string> set_remaining_Piece;

    for(const auto& [key, value] : (*PTR_board))
    {
        if (value.contains("w") || value.contains("b"))
        {
            set_remaining_Piece.insert(value);
        }
    }
    if (std::size(set_remaining_Piece) == 2 && set_remaining_Piece.contains("wK") && set_remaining_Piece.contains("bK"))
    {
        return true;
    }
    else if (std::size(set_remaining_Piece) == 3 && set_remaining_Piece.contains("wK") && set_remaining_Piece.contains("bK") && (set_remaining_Piece.contains("bB") || set_remaining_Piece.contains("wB")))
    {
        return true;
    }
    else if (std::size(set_remaining_Piece) == 3 && set_remaining_Piece.contains("wK") && set_remaining_Piece.contains("bK") && (set_remaining_Piece.contains("bN") || set_remaining_Piece.contains("wN")))
    {
        return true;
    }
    else if (std::size(set_remaining_Piece) == 4 && set_remaining_Piece.contains("wK") && set_remaining_Piece.contains("bK") && 
    (set_remaining_Piece.contains("bN") || set_remaining_Piece.contains("bB")) && (set_remaining_Piece.contains("wN") || set_remaining_Piece.contains("wB")))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::move_rule_status() noexcept
{
    if (n_no_capture_or_pawn == 50)
    {
        std::cout << "Fifty-move rule, a draw may be claimed." << std::endl;
        claimed_draw = true;
        return false;
    }
    else if (n_no_capture_or_pawn == 75)
    {
        std::cout << "Draw by Seventy-five-move rule." << std::endl;
        return true;
    }
    else
    {
        claimed_draw = false;
        return false;
    }
}

bool Player::repetition_rule_status() noexcept
{   
    if (all_w_move[n_total_w_move] == all_w_move[n_total_w_move-2] && _color_player == "w")
    {
        n_w_repetition++;
        std::cout << "repetiton w : " << n_w_repetition << std::endl;
    }
    else if (all_b_move[n_total_b_move] == all_b_move[n_total_b_move-2] && _color_player == "b")
    {
        n_b_repetition++;
        std::cout << "repetiton b : " << n_b_repetition << std::endl;
    }
    else
    {
        if (_color_player == "w")
        {
            n_w_repetition = 0;
        }
        else if(_color_player == "b")
        {
            n_b_repetition = 0;
        }
    }
    
    if(n_w_repetition == 3 || n_b_repetition == 3)
    {
        std::cout << "Threefold repetition rule, a draw may be claimed." << std::endl;
        claimed_draw = true;
        return false;
    }
    else if (n_w_repetition == 5 || n_b_repetition == 5)
    {
        std::cout << "Draw by Fivefold repetition rule." << std::endl;
        return true;
    } 
    else
    {
        return false;
    }
     
} 

bool Player::move_piece(bool check_or_not, const std::string piece_case, const std::string target_case) noexcept // 'check_or_not' : si c'est une vérification de case disponnible ou non
{   
    /*if (check_or_not == false && _color_player == "b")
    {
        for (const auto& [key, value] : all_b_move)
        {
            std::cout << key << " : " << value << std::endl;
        }
    }*/

    if (piece_case == "draw" && draw == false)
    {
        draw = true;
        std::cout << "Draw offer by " << _color_player << "." << std::endl;
        return false;
    }
    else if (draw == true && piece_case == "draw")
    {
        std::cout << "Draw by mutual agreement." << std::endl;
        set_status(PlayerStatus::draw);
        return false;
    }
    else if(draw == true && piece_case != "draw")
    {
        draw = false;
        std::cout << "Draw disagree by " << _color_player << "." << std::endl;
    }

    if (dead_position_status() == true && check_or_not == false)
    {
        std::cout << "Draw by insufficient material." << std::endl;
        set_status(PlayerStatus::draw);
        return false;
    }

    if (check_or_not == false)
    {
        case_king.clear();
    }
    
    
    if (((n_move_w > 0 && _color_player == "w") || (n_move_b > 0 && _color_player == "b")) && check_or_not == false && check_enemies == true) // vérifie si le joueur est en MAT
    {
        if (checkmate_stalemate_status() == true)
        {
            set_status(PlayerStatus::checkmate);
            std::cout << _color_player << " is in checkmate." << std::endl;
            check_enemies = false;
            return false;
        }
    }

    else if (((n_move_w > 0 && _color_player == "w") || (n_move_b > 0 && _color_player == "b")) && check_or_not == false && check_enemies == false) // vérifie si le joueur est en PAT
    {
        check_status(true);
        if (checkmate_stalemate_status() == true && n_movable_piece == 0)
        {
            set_status(PlayerStatus::stalemate);
            std::cout << _color_player << " is in stalemate." << std::endl;
            return false;
        }
    }
    
    if (check_or_not == false && check_enemies == true) // vérifie si le joueur est en echec
    {
        check_enemies = false;
        set_status(PlayerStatus::check);
        std::cout << _color_player << " is in check." << std::endl;
        std::cout << "le responsable est aa : " << check_responsable << std::endl;
    }
    
    
    bool can_move = false;
    bool pawn_can_move = false;
    bool pawn_can_take = false;
    bool kingside_castling = false;
    bool queenside_castling = false;
    int piece_letter_to_n = piece_case[0] - '0'; // converti la lettre de la colonne correspondante en nombre
    // a = 49 ; b = 50 ; etc
    int target_letter_to_n = target_case[0] - '0'; // converti la lettre de la colonne correspondante en nombre
    
    if ((*PTR_board)[piece_case].contains(_color_player + " ") && (_status == PlayerStatus::ongoing || (_status == PlayerStatus::check && (target_case == check_responsable || case_between_king.contains(target_case))))) // règle de déplacement du pion
    {   
        if (_color_player == "w")
        {
            if ((same_color_global == false && (*PTR_board)[piece_case].contains("w")) || (*PTR_board)[piece_case].contains("w"))
            {
                if ((target_case.contains(piece_case[0]) && target_case.contains(piece_case[1] - 1))) // autorise de prendre une pièce adverse
                {
                    if ((*PTR_board)[target_case] == "# " || (*PTR_board)[target_case] == "@ ")
                    {
                        pawn_can_move = true;
                        can_move = true;
                    }
                }
                if (piece_case.contains("7") && target_case.contains(piece_case[0]) && target_case.contains(piece_case[1] - 2))
                {
                    if ((*PTR_board)[target_case] == "# " || (*PTR_board)[target_case] == "@ ")
                    {
                        pawn_can_move = true;
                        can_move = true;
                    }
                }
                if ((*PTR_board)[target_case].contains("b") && target_case.contains(piece_case[1] - 1) && (target_letter_to_n == piece_letter_to_n+1 || target_letter_to_n == piece_letter_to_n-1))
                {
                    if (!target_case.contains("K")) // sauf le roi
                    {
                        pawn_can_move = true;
                        can_move = true;
                        pawn_can_take = true;
                    }
                }
                else if ((*PTR_board)[target_case].contains("b") && target_case.contains(piece_case[1] - 1) && (target_letter_to_n == piece_letter_to_n+1 || target_letter_to_n == piece_letter_to_n-1))
                // sert à empêcher le roi de se déplacer vers une case prennable par un pion.
                // mais le pion ne peut pas se déplacer vers cette case, car elle ne contient pas de pièce adverse
                {
                    pawn_can_take = true;
                }
                
            }
        }
        else if ((same_color_global == false && (*PTR_board)[piece_case].contains("b")) || _color_player == "b")
        {
            if ((*PTR_board)[piece_case].contains("b"))
            {
                if ((target_case.contains(piece_case[0]) && target_case.contains(piece_case[1] + 1)) || 
                    (target_case.contains(piece_case[1] + 1) && (target_letter_to_n == piece_letter_to_n+1 || target_letter_to_n == piece_letter_to_n-1) && (*PTR_board)[target_case].contains("w"))) // autorise de prendre une pièce adverse
                {
                    if ((*PTR_board)[target_case] == "# " || (*PTR_board)[target_case] == "@ ")
                    {
                        pawn_can_move = true;
                        can_move = true;
                    }
                }
                if (piece_case.contains("2") && target_case.contains(piece_case[0]) && target_case.contains(piece_case[1] + 2))
                {
                    if ((*PTR_board)[target_case] == "# " || (*PTR_board)[target_case] == "@ ")
                    {
                        pawn_can_move = true;
                        can_move = true;
                    }
                }
                if ((*PTR_board)[target_case].contains("w") && target_case.contains(piece_case[1] + 1) && (target_letter_to_n == piece_letter_to_n+1 || target_letter_to_n == piece_letter_to_n-1))
                {
                    if (!target_case.contains("K")) // sauf le roi
                    {
                        pawn_can_move = true;
                        can_move = true;
                        pawn_can_take = true;
                    }
                }
                else if ((*PTR_board)[target_case].contains("w") && target_case.contains(piece_case[1] - 1) && (target_letter_to_n == piece_letter_to_n+1 || target_letter_to_n == piece_letter_to_n-1))
                // sert à empêcher le roi de se déplacer vers une case prennable par un pion.
                // mais le pion ne peut pas se déplacer vers cette case, car elle ne contient pas de pièce adverse
                {
                    pawn_can_take = true;
                }
            }
            if (target_case.contains("8"))
            {
                if (((*PTR_board)[target_case] == "# " || (*PTR_board)[target_case] == "@ ") && check_or_not == false)
                {
                    std::string new_piece;
                    while (1)
                    {
                        std::cout << "Choose which piece replaces the Pawn : ";
                        std::cin >> new_piece;
                        if (new_piece != " " && new_piece != "R" && new_piece != "N" && new_piece != "B" && new_piece != "Q")
                        {
                            continue;
                        }
                        else{break;}
                    }
                    (*PTR_board)[piece_case] = _color_player + new_piece;
                    can_move = true;
                }
            }
        }
    }
    else if (((*PTR_board)[piece_case].contains("R") || (*PTR_board)[piece_case].contains("Q")) && (_status == PlayerStatus::ongoing || (_status == PlayerStatus::check && (target_case == check_responsable || case_between_king.contains(target_case))))) 
    // règle de déplacement de la tour et partiellement de la dame
    {
        int piece_letter_to_n = piece_case[0] - '0'; // converti la lettre de la colonne correspondante en nombre
        // a = 49 ; b = 50 ; etc
        int target_letter_to_n = target_case[0] - '0'; // converti la lettre de la colonne correspondante en nombre

        if ((target_case.contains(piece_case[0]) && !target_case.contains(piece_case[1])) || (!target_case.contains(piece_case[0]) && target_case.contains(piece_case[1])))
        {
            if (same_color_global == false || (!(*PTR_board)[target_case].contains("b") && _color_player == "b" && (*PTR_board)[piece_case].contains("b")) || 
            (!(*PTR_board)[target_case].contains("w") && _color_player == "w" && (*PTR_board)[piece_case].contains("w"))) // si la valeur de 'target_case' ne contient PAS la couleur du joueur
            // autorise de prendre une pièce adverse
            {
                if (!target_case.contains("K")) // sauf le roi
                    {
                        can_move = true;
                    }
            }
            int difference;

            if (target_case.contains(piece_case[0]))
            {
                int second_char = piece_case[1] - '0';
                if (target_case[1] > piece_case[1])
                {
                    difference = target_case[1] - piece_case[1];
                }
                else
                {
                    difference = piece_case[1] - target_case[1];
                }
                for (auto i = 0; i < difference-1; i++) // pour chaque case entre la 'piece_case' et la 'target_case'
                {
                    std::string key;
                    if (target_case[1] > piece_case[1])
                    {
                        //int second_char = piece_case[1] - '0';
                        second_char += i;
                        second_char++;
                        key.push_back(target_case[0]);
                        key.push_back(second_char + '0');

                        if ((*PTR_board)[key] != _initial_board_content[key] || (*PTR_board)[key] != _initial_board_content[key]) // si la case entre contient un pièce :
                        {
                            can_move = false; // la tour ne peut pas se déplacer
                            break;
                        } 
                    }  
                    else
                    {
                        //int second_char = piece_case[1] - '0';
                        second_char -= i;
                        second_char--;
                        key.push_back(target_case[0]);
                        key.push_back(second_char + '0');

                        for (const auto& [k, v] : piece_initial_board_content) 
                        {
                            bool yes_or_no = false;
                            for (const auto& [key, value] : _initial_board_content)
                            {
                                if (k == key)
                                {
                                    yes_or_no = true;
                                } 
                            }
                            if (yes_or_no == false) // si, non
                            {
                                piece_initial_board_content.erase(k); // elle est supprimé
                            }
                        }

                        if ((*PTR_board)[key] != _initial_board_content[key] || (*PTR_board)[key] != _initial_board_content[key])
                        {
                            can_move = false;
                            break;
                        }
                    }
                }
            }  
            else
            {
                int first_char = piece_letter_to_n;
                if (target_letter_to_n > piece_letter_to_n)
                {
                    difference = target_letter_to_n - piece_letter_to_n;
                }
                else
                {
                    difference = piece_letter_to_n - target_letter_to_n;
                }
                for (auto i = 1; i < difference; i++) // pour chaque case entre la 'piece_case' et la 'target_case'
                {
                    std::string key;
                    if (target_letter_to_n > piece_letter_to_n)
                    {
                        //first_char += i;
                        first_char++;
                        key.push_back(first_char + '0');
                        key.push_back(target_case[1]);
                        if ((*PTR_board)[target_case] == "wK")
                        {
                            std::cout << "case testé : " << key << std::endl;
                            std::cout << first_char << " et " << first_char+'0' << std::endl;
                        }

                        if ((*PTR_board)[key] != _initial_board_content[key]) // si la case entre contient un pièce :
                        {
                            can_move = false; // la tour ne peut pas se déplacer
                            break;
                        }
                        else if ((*PTR_board)[key] == _initial_board_content[key])
                        {
                            if ((*PTR_board)[target_case].contains("K") && check_or_not == true && can_move == true)
                            {   
                                case_between_king.insert(key);
                            }
                            
                        }
                    }  
                    else
                    {
                        //first_char -= i;
                        first_char--;
                        key.push_back(first_char + '0');
                        key.push_back(target_case[1]);

                        if ((*PTR_board)[key] != _initial_board_content[key])
                        {
                            can_move = false;
                            break;
                        }
                        else
                        {
                            if ((*PTR_board)[target_case].contains("K") && check_or_not == true && can_move == true)
                            {
                                case_between_king.insert(key);
                            }
                        }
                    }
                }
            }
            
        } 
    } 
    else if ((*PTR_board)[piece_case].contains("N") && (_status == PlayerStatus::ongoing || (_status == PlayerStatus::ongoing || (_status == PlayerStatus::check && (target_case == check_responsable || case_between_king.contains(target_case)))))) 
    // règle de déplacement du cavalier
    {
        //int piece_letter_to_n = piece_case[0] - '0'; // converti la lettre de la colonne correspondante en nombre
        // a = 49 ; b = 50 ; etc
        //int target_letter_to_n = target_case[0] - '0'; // converti la lettre de la colonne correspondante en nombre

        if ((target_case.contains(piece_case[1] + 2) || target_case.contains(piece_case[1] - 2 )) && (target_letter_to_n == piece_letter_to_n + 1 || target_letter_to_n == piece_letter_to_n - 1))
        {
            if (same_color_global == false || (!(*PTR_board)[target_case].contains("b") && _color_player == "b" && (*PTR_board)[piece_case].contains("b")) || 
            (!(*PTR_board)[target_case].contains("w") && _color_player == "w" && (*PTR_board)[piece_case].contains("w"))) // si la valeur de 'target_case' ne contient PAS la couleur du joueur
            // autorise de manger une pièce adverse
            {
                if (!target_case.contains("K")) // sauf le roi
                {
                    can_move = true;
                }
            }
        }
        else if ((target_letter_to_n == piece_letter_to_n + 2 || target_letter_to_n == piece_letter_to_n - 2) && (target_case.contains(piece_case[1] + 1) || target_case.contains(piece_case[1] - 1 )))
        {
            if (same_color_global == false || ((*PTR_board)[target_case] != "b" && _color_player == "b") || ((*PTR_board)[target_case] != "w" && _color_player == "w")) // si la valeur de 'target_case' ne contient PAS la couleur du joueur
            // autorise de manger une pièce adverse
            {
                if (!target_case.contains("K")) // sauf le roi
                {
                    can_move = true;
                }
            }
        }
    }
    if (((*PTR_board)[piece_case].contains("B") || (*PTR_board)[piece_case].contains("Q")) && (_status == PlayerStatus::ongoing || (_status == PlayerStatus::check && (target_case == check_responsable || case_between_king.contains(target_case))))) 
    // règle de déplacement du fou et partiellement de la dame
    {
        int second_char = piece_case[1] - '0';
        int difference_first;
        int difference_second;

        if (target_case[1] > piece_case[1])
        {
            difference_first = target_case[1] - piece_case[1];
        }
        else
        {
            difference_first = piece_case[1] - target_case[1];
        }
        if (target_letter_to_n > piece_letter_to_n)
        {
            difference_second = target_letter_to_n - piece_letter_to_n;
        }
        else
        {
            difference_second = piece_letter_to_n - target_letter_to_n;
        }
        if (difference_first == difference_second)
        {
            if (same_color_global == false || (!(*PTR_board)[target_case].contains("b") && _color_player == "b" && (*PTR_board)[piece_case].contains("b")) || 
            (!(*PTR_board)[target_case].contains("w") && _color_player == "w" && (*PTR_board)[piece_case].contains("w")))
            // si la valeur de 'target_case' ne contient PAS la couleur du joueur
            // autorise de manger une pièce adverse
            {
                if (!target_case.contains("K")) // sauf le roi
                {
                    can_move = true;
                }
                else if (target_case.contains("K") && check_or_not == true)
                {
                    can_move = true;
                }
            }

            for (auto i = 1; i < difference_first; i++) // pour chaque case entre la 'piece_case' et la 'target_case'
            {
                std::string key;
                if (target_letter_to_n > piece_letter_to_n) // si le déplacement se fait à gauche
                {
                    //piece_letter_to_n += i;
                    piece_letter_to_n++;
                }
                else // si le déplacement se fait à droite
                {
                    //piece_letter_to_n -= i;
                    piece_letter_to_n--;
                }
                if (target_case[1] > piece_case[1]) // si le déplacement se fait en haut
                {
                    //second_char += i;
                    second_char++;
                }
                else // si le déplacement se fait en bas
                {
                    //second_char -= i;
                    second_char--;
                }
                
                key.push_back(piece_letter_to_n + '0');
                key.push_back(second_char + '0');

                /*if (target_case == "e1")
                {
                    std::cout << key << std::endl;
                }*/

                if ((*PTR_board)[key] != _initial_board_content[key] && difference_first == difference_second) // si la case entre contient un pièce :
                {
                    //std::cout << key << "  ::  " << (*PTR_board)[key] << std::endl;
                    can_move = false; // le fou et la dame ne peuvent pas se déplacer
                    break;
                }
                else
                {
                    if ((*PTR_board)[target_case].contains("K") && check_or_not == true && can_move == true)
                    {
                        case_between_king.insert(key);
                    }
                }
            } 
        }
    }
    else if ((*PTR_board)[piece_case].contains("K")) // règles de déplacement du roi
    {
        if ((target_letter_to_n == piece_letter_to_n+1 || target_letter_to_n == piece_letter_to_n-1 || target_letter_to_n == piece_letter_to_n) && (target_case.contains(piece_case[1]) || target_case.contains(piece_case[1]-1) || target_case.contains(piece_case[1]+1)) 
        && !case_check.contains(target_case))
        // '!case_check.contains(target_case)' : le roi ne doit pas aller dans un case qui le mettrait en échec
        {
            if (same_color_global == false || (!(*PTR_board)[target_case].contains("b") && _color_player == "b" && (*PTR_board)[piece_case].contains("b")) || 
            (!(*PTR_board)[target_case].contains("w") && _color_player == "w" && (*PTR_board)[piece_case].contains("w")))
            {
                if (!target_case.contains("K")) // sauf le roi
                {   
                    can_move = true;
                }
            }
        }
        if (can_move == true)
        {
            std::string target_case_next_column;
            char next_first_char = target_letter_to_n + 1 + '0';
            target_case_next_column.push_back(next_first_char);
            target_case_next_column.push_back(target_case[1]);

            std::string target_case_prev_column;
            char prev_first_char = target_letter_to_n - 1 + '0';
            target_case_prev_column.push_back(prev_first_char);
            target_case_prev_column.push_back(target_case[1]);

            std::string target_case_next_line;
            int n_next_second_char = target_case[1] - '0' + 1;
            char next_second_char = n_next_second_char + '0';
            target_case_next_line.push_back(target_case[0]);
            target_case_next_line.push_back(next_second_char);

            std::string target_case_prev_line;
            int n_prev_second_char = target_case[1] - '0' - 1;
            char prev_second_char = n_prev_second_char + '0';
            target_case_prev_line.push_back(target_case[0]);
            target_case_prev_line.push_back(prev_second_char);

            std::string target_case_prev_prev;
            target_case_prev_prev.push_back(prev_first_char);
            target_case_prev_prev.push_back(prev_second_char);

            std::string target_case_prev_next;
            target_case_prev_next.push_back(prev_first_char);
            target_case_prev_next.push_back(next_second_char);

            std::string target_case_next_next;
            target_case_next_next.push_back(next_first_char);
            target_case_next_next.push_back(next_second_char);

            std::string target_case_next_prev;
            target_case_next_prev.push_back(next_first_char);
            target_case_next_prev.push_back(prev_second_char);

            //std::cout << target_case_next_column << '\n' << target_case_next_line << '\n' << target_case_prev_column << '\n' << target_case_prev_line << '\n' << target_case_next_next << '\n' << target_case_next_prev << '\n' << target_case_prev_prev << '\n' << target_case_prev_next << std::endl;
            if ((((*PTR_board)[target_case_prev_column].contains("K") && target_case_prev_column != piece_case) || ((*PTR_board)[target_case_next_column].contains("K") && target_case_next_column != piece_case) 
            || ((*PTR_board)[target_case_next_line].contains("K") && target_case_next_line != piece_case) || ((*PTR_board)[target_case_prev_line].contains("K") && target_case_prev_line != piece_case)
            || ((*PTR_board)[target_case_prev_prev].contains("K") && target_case_prev_prev != piece_case) || ((*PTR_board)[target_case_prev_next].contains("K") && target_case_prev_next != piece_case) 
            || ((*PTR_board)[target_case_next_next].contains("K") && target_case_next_next != piece_case) || ((*PTR_board)[target_case_next_prev].contains("K") && target_case_next_prev != piece_case)))
            {
                can_move = false;
            }
            
        }
        else if (((*PTR_board)[piece_case].contains("w") && _color_player == "w") && check_or_not == false)
        {
            if (target_case == "g1" && (*PTR_board)["e1"].contains("bK") && (piece_case == "e1" && (*PTR_board)["g1"] == "# " && (*PTR_board)["f1"] == "@ "))
            // petit roque (king side)
            {
                can_move = false;
                kingside_castling = true;
                (*PTR_board)[target_case] = (*PTR_board)[piece_case];
                (*PTR_board)[piece_case] = _initial_board_content[piece_case];
                (*PTR_board)["f8"] = (*PTR_board)["h8"];
                (*PTR_board)["h8"] = _initial_board_content["h8"];
                return true;
            }
            else if (target_case == "b1" && (*PTR_board)["e1"].contains("bK") && (piece_case == "e1" && (*PTR_board)["c1"] == "# " && (*PTR_board)["d1"] == "@ "))
            // grand roque (queen side)
            {
                can_move = false;
                queenside_castling = true;
                (*PTR_board)[target_case] = (*PTR_board)[piece_case];
                (*PTR_board)[piece_case] = _initial_board_content[piece_case];
                (*PTR_board)["c8"] = (*PTR_board)["a8"];
                (*PTR_board)["a8"] = _initial_board_content["a8"];
                return true;
            } 
        }
        else if ((*PTR_board)[piece_case].contains("b") && _color_player == "b" && check_or_not == false)
        {
            if (target_case == "g1" && (*PTR_board)["e1"].contains("bK") && (piece_case == "e1" && (*PTR_board)["g1"] == "# " && (*PTR_board)["f1"] == "@ "))
            // petit roque (king side)
            {
                can_move = false;
                kingside_castling = true;
                (*PTR_board)[target_case] = (*PTR_board)[piece_case];
                (*PTR_board)[piece_case] = _initial_board_content[piece_case];
                (*PTR_board)["f1"] = (*PTR_board)["h1"];
                (*PTR_board)["h1"] = _initial_board_content["h1"];
                return true;
            }
            else if (target_case == "b1" && (*PTR_board)["e1"].contains("bK") && (piece_case == "e1" && (*PTR_board)["c1"] == "# " && (*PTR_board)["d1"] == "@ "))
            // grand roque (queen side)
            {
                can_move = false;
                queenside_castling = true;
                (*PTR_board)[target_case] = (*PTR_board)[piece_case];
                (*PTR_board)[piece_case] = _initial_board_content[piece_case];
                (*PTR_board)["c1"] = (*PTR_board)["a1"];
                (*PTR_board)["a1"] = _initial_board_content["a1"];
                return true;
            } 
        }
    }
    
    bool yes_or_no = false;
    for (const auto& [key, value] : _initial_board_content)
    {
        if (target_case == key) // vérifie si la 'target_case' existe
        {
            yes_or_no = true;
            break;
        } 
    }

    if (yes_or_no == false) // si, non
    {
        (*PTR_board)[target_case].erase(); // elle est supprimé
        can_move = false;
        pawn_can_move = false;
        pawn_can_take = false;
    }

    if ((can_move == true || pawn_can_move == true) && check_or_not == false)
    {
        std::string backup_target_case = (*PTR_board)[target_case];
        std::string backup_piece_case = (*PTR_board)[piece_case];

        (*PTR_board)[target_case] = (*PTR_board)[piece_case]; // le contenue de la 'target_case' devient la pièce de la 'piece_case'
        (*PTR_board)[piece_case] = _initial_board_content[piece_case]; // le contenue de la 'piece_case' devient un carreau du plateau
        set_status(PlayerStatus::ongoing);

        case_check.clear(); // supprime le contenue de cette variable, car toutes les cases possible doivent reêtre définie après chaque mouvement
        check_status(false); // vérifie si le mouvement n'a pas mis le roi en échec
        same_color_global = true;
        if (check_enemies == true)
        {
            (*PTR_board)[target_case] = backup_target_case;
            (*PTR_board)[piece_case] = backup_piece_case;
            can_move = false;
            check_enemies = false;
            std::cout << "Wrong piece or target case." << std::endl;
            return false;
        }
        
        case_check.clear();
        check_status(true);

        if (_color_player == "w")
        {
            n_move_w++;
        }
        else{n_move_b++;}

        n_total_move++;
        all_move[n_total_move] = piece_case + "->" + target_case;

        if (_color_player == "w")
        {
            n_total_w_move++;
            all_w_move[n_total_w_move] = piece_case + "->" + target_case;
        }
        else if (_color_player == "b")
        {
            n_total_b_move++;
            all_b_move[n_total_b_move] = piece_case + "->" + target_case;
        }
        
        
        if ((backup_target_case == "# " || backup_target_case == "@ ") && ((*PTR_board)[target_case] != "b " || (*PTR_board)[target_case] != "w "))
        {
            n_no_capture_or_pawn++;
            //std::cout << " n : " << n_no_capture_or_pawn << std::endl;
        }
        else
        {
            n_no_capture_or_pawn = 0;
        }
        if (repetition_rule_status() == true)
        {
            set_status(PlayerStatus::draw);
        }

        if (move_rule_status() == true)
        {
            set_status(PlayerStatus::draw);
        }
        
        return true; // le plateau sera affiché
    }
    else if ((kingside_castling == false || queenside_castling == false) && check_or_not == false)
    {
        std::cout << "Wrong piece or target case." << std::endl;
        return false; // le plateau ne sera pas affiché
    }

    else if ((can_move == true || pawn_can_take == true) && check_or_not == true)
    {   
        bool yes_or_no = false;
        for (const auto& [key, value] : _initial_board_content)
        {
            if (target_case == key)
            {
                yes_or_no = true;
            } 
        }
        if (!(*PTR_board)[piece_case].contains("K") && yes_or_no == true)
        {
            //std::cout << n_movable_piece << " " << piece_case << " : " << target_case << std::endl;
            case_check.insert( target_case );
            n_movable_piece++;

            if ((*PTR_board)[target_case].contains("K"))
            {
                //std::cout << "responsable : " << (*PTR_board)[piece_case] << " key : " << piece_case << std::endl; 
                check_responsable = piece_case; 
                std::cout << "le responsbal est : " << check_responsable << std::endl;
                //std::cout << (*PTR_board)[target_case] << std::endl;
                check_enemies = true;
            }
        } 

        else if(((*PTR_board)[piece_case].contains("K") && !(*PTR_board)[target_case].contains("K")))
        {
            case_king.insert( target_case );
        }
        if(target_case == check_responsable)
        {
            case_king.insert( piece_case );
        }   
    }
    
    return false; // le plateau ne sera pas affiché
}
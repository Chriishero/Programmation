#include "include\player.hpp"
#include "include\game_status.hpp"
#include <iostream>
#include <vector>

std::vector<int> _player_array;

std::vector<int> Player::get_player_array() const noexcept
{
    return _player_array;
}

void Player::set_player_array(int n_player) const noexcept
{
    for (auto i = 1; i <= n_player; i++)
    {
        _player_array.push_back(i);
    }
}

void Player::delete_player(int player) const noexcept
{
    _player_array[player-1] = 0;
}

void Player::show_player_array() const noexcept
{
    for (const auto& element : _player_array)
    {
        std::cout << element << std::endl;
    }
    
}

bool Player::check_win_multiplayer_default() const noexcept
{
    int n = 0;
    bool win = false;
    for (const auto& element : _player_array)
    {
        if (element != 0)
        {
            n++;
        }
    }

    if (n == 1)
    {
        win = true;
    }
    
    return win;
}

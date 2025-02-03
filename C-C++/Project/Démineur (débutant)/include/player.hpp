#ifndef __PLAYER__
    #define __PLAYER__
    #include <vector>

    class Player
    {
        public:
            std::vector<int> get_player_array() const noexcept;
            void set_player_array(int n_player) const noexcept;
            void delete_player(int player) const noexcept;
            void show_player_array() const noexcept;
            bool check_win_multiplayer_default() const noexcept;
    };

#endif
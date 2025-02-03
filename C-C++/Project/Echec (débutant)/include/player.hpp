#ifndef __PLAYER__
    #define __PLAYER__
    #include "gameinit.hpp"
    #include "enum.hpp"
    #include <string>

    class Player : public GameInit
    {
        using GameInit::GameInit;

        public:
            Player() = delete;
            Player(Mode mode, PlayerStatus status, std::string color_player) noexcept;

            void set_status(PlayerStatus status) noexcept;
            PlayerStatus get_status() const noexcept;
            std::string get_color_player() const noexcept;
            void check_status(bool same_color) noexcept;
            bool checkmate_stalemate_status() noexcept;
            bool dead_position_status() noexcept;
            bool move_rule_status() noexcept;
            bool repetition_rule_status() noexcept;
            bool move_piece(bool check_or_not, const std::string piece_case, const std::string target_case) noexcept;

        private:
            Mode _mode;
            PlayerStatus _status;
            std::string _color_player;
        
    };

#endif
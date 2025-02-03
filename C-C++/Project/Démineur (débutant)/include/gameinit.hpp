#ifndef __GAMEINIT__
    #define __GAMEINIT__
    #include <string>
    #include <array>
    #include "game_status.hpp"

    class GameInit
    {
        public:
            GameInit() = delete;
            GameInit(int n_player, const int area_size, const int area_width, const int area_height, Game_status status, int difficulty) noexcept;

            Game_status get_status() const noexcept;

            void generate_mine() const noexcept;
            void check_mine_around(int selected_case, int player) const noexcept;
            void generate_area() const noexcept;
            void new_area(int selected_case, int player) const noexcept;
            void set_status(Game_status status);
            void show_mine_area() const noexcept;
            void convert_selected_case(std::array<int, 2>& case_coordinate, int& selected_case) const noexcept;

            void set_base_point(int n_player) const noexcept;
            void set_point(int player) const noexcept;
            int get_point(int player) const noexcept;
            void show_point_array() const noexcept;
            void point_to_zero(int player) const noexcept;
            
            bool check_win_solo() const noexcept;
            bool check_win_multiplayer_point(bool check_default_win) const noexcept;

        protected:
            int _n_player;
            const int _area_size;
            const int _area_width;
            const int _area_height;
            Game_status _status;
            int _difficulty;
    };

#endif
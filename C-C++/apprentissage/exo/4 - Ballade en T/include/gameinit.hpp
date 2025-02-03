#ifndef __GAMEINIT__
    #define __GAMEINIT__
    #include <vector>
    #include <string>

    class GameInit
    {
        GameInit() = delete;

        public:
            GameInit(int area_height, int area_width, int starting_position) noexcept;

            void init_area() const noexcept;
            void set_player_position(std::string button) const noexcept;

        protected:
            int _area_height;
            int _area_width;
            int _starting_position;
    };

#endif
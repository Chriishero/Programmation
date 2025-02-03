#ifndef __GAMEINIT__
    #define __GAMEINIT__
    #include <map>
    #include <string>

    class GameInit
    {
        public:
            GameInit() noexcept;
            
            void generate_board() noexcept;
            std::map<std::string, std::string> get_board() const noexcept;

        protected:
            std::map<std::string, std::string> _initial_board_content;
            std::map<std::string, std::string> piece_initial_board_content;
    };

#endif
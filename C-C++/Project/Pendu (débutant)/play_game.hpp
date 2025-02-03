#ifndef __PLAYGAME__
    #define __PLAYGAME__
    #include "game_init.hpp"
    #include "pendu_status.hpp"
    #include <string>
    #include <list>

    class PlayGame : public GameInit
    {
        using GameInit::GameInit;
        
        public : 
            PlayGame() = delete;
            PlayGame(const std::string& word, const std::list<char>& word_letter_list, Pendu_status status) noexcept;

            std::list<char> right_word_letter_list(bool help_word) const noexcept;
            void wrong_letter(int& fail_number) noexcept;
            void enter_letter(bool help_word) noexcept;
            void show_right_letter(const std::list<char>& word_letter_list, bool help_world) const noexcept;


        private :
            std::list<char> _word_letter_list;
    };
    
#endif
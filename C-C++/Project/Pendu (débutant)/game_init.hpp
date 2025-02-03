#ifndef __GAMEINIT__
    #define __GAMEINIT__
    #include "pendu_status.hpp"
    #include <string>
    #include <list>

    class GameInit
    {
        public:
            GameInit() = delete;
            GameInit(const std::string& word, Pendu_status status) noexcept;

            std::string get_word() const noexcept;
            int lenght_word() const noexcept;
            std::string underscore_letter(bool help_word) const noexcept;
            std::string get_firstletter(const std::string& word) const noexcept;
            std::list<char> word_letter_list() const noexcept;
            Pendu_status get_status() const noexcept;
            void set_status(Pendu_status status);

        private:
            std::string _word;
            Pendu_status _status;
    };

#endif
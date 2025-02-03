#ifndef __QUEST__
    #define __QUEST__
    #include "quest_status.hpp"
    #include <string>

    /*
    Classe A, Classe B
        Héritage : B est une sorte de A
        Composition : B fait parti de A

    'Quest_status' fait parti de 'Quest' : composition
    */

    class Quest
    {
        public: 
            Quest() = delete;
            Quest(const std::string& name, const std::string& description, int unit_id) noexcept;
            void show_quest_info() const noexcept;

        private: 
            std::string _name;
            std::string _description;
            int _unit_id;
            Quest_status _status; // relation de composition entre la class 'Quest' et l'enum class 'Quest_status', 'Quest' contient une des instances de 'Quest_status'
    };

#endif

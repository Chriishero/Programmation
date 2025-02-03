#include "unit.hpp"
#include "character.hpp"
#include "quest.hpp"
#include <iostream>

int main()
{
    Unit npc{114, "Villager"};
    std::cout << "ID du NPC : " << npc.get_id() << std::endl; // appelle de l'attribut privé '_id' depuis le getter 'get_id()'
    std::cout << "Nom du NPC : " << npc.get_name() << std::endl;

    Character c{1, "Chrishero", 666};
    std::cout << "ID du personnage : " << c.get_id() << std::endl;
    std::cout << "Nom du personnage : " << c.get_name() << std::endl;
    std::cout << "Niveau du personnage : " << c.get_level() << std::endl;

    Quest q{"Tourte au sanglier", "Rapporter 5 morceaux de viande.", npc.get_id()};
    q.show_quest_info();


    return 0;
}
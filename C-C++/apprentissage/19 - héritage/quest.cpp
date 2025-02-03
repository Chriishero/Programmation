#include "quest.hpp"
#include "quest_status.hpp"
#include <iostream>
#include <string>

Quest::Quest(const std::string& name, const std::string& description, int unit_id) noexcept : _name(name), _description(description), _unit_id(unit_id)
{
    _status = Quest_status::disabled; // au lancement du constructeur, initialiser l'enum class à sa valeur disabled
}

void Quest::show_quest_info() const noexcept
{
    std::cout <<"Nom de la quete : " << _name << "\nDescription : " << _description << "\nID de la source de la quete : " << _unit_id << std::endl;
}
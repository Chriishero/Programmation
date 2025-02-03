#include "character.hpp"
#include <iostream>
#include <string>

Character::Character(int id, const std::string& name, int level) noexcept : Unit(id, name), // les paramètres id et name sont transmis au constructeur de la classe parent 'Unit'
 _level(level) //  level doit être attribué car il fait partie de la classe enfant 'Character'
{
}

int Character::get_level() const noexcept
{
    return _level;
}
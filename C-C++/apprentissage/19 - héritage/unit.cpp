#include "unit.hpp"
#include <iostream>
#include <string>

Unit::Unit(int id, const std::string& name) noexcept : _id(id), _name(name) // initialise le constructeur et injecte le paramètre (variable) 'id' dans l'attribut '_it' de la classe 'Unit', etc
{ // pour que le 'noexcept' fonctionne sur une variable 'string', elle doit être constante
}

int Unit::get_id() const noexcept
{
    return _id; // retourne l'attribut '_id' de la classe 'Unit"
}

std::string Unit::get_name() const noexcept
{
    return _name; // retourne l'attribut '_name' de la classe 'Unit"
}
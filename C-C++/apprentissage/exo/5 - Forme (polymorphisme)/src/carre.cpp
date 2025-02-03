#include "../include/carre.hpp"
#include <iostream>

Carre::Carre(float cote) noexcept : _cote(cote)
{}

void Carre::aire() const noexcept
{
    std::cout << "Aire du carre : " << _cote * _cote << std::endl;
}
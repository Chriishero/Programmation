#include "../include/rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(float longueur, float largeur) noexcept : _longueur(longueur), _largeur(largeur)
{}

void Rectangle::aire() const noexcept
{
    std::cout << "Aire du rectangle : " << _longueur * _largeur << std::endl;
}
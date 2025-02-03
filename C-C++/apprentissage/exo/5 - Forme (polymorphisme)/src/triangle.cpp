#include "../include/triangle.hpp"
#include <iostream>

Triangle::Triangle(float base, float hauteur) noexcept : _base(base), _hauteur(hauteur)
{}

void Triangle::aire() const noexcept
{
    std::cout << "Aire du triangle : " << _base*_hauteur << std::endl;
}
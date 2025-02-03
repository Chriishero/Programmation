#include "../include/cercle.hpp"
#include <iostream>

Cercle::Cercle(float rayon) noexcept : _rayon(rayon)
{}

void Cercle::aire() const noexcept
{
    const double PI = 3.14159265358979224;
    std::cout << "Aire du cercle : " << PI * (_rayon * _rayon) << std::endl;
}
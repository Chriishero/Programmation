#include "point.hpp"
#include <iostream>

Point::Point()
{
    std::cout << "Creation d'un point : " << this << std::endl; // this fait référence à l'objet en question qui est en cours
}

Point::~Point()
{
    std::cout << "Destruction de l'object : " << this << std::endl;
}
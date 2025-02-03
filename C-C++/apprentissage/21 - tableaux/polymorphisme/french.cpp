#include "french.hpp"
#include <iostream>

void French::sayGoodNight() const noexcept
{ 
    std::cout << _name << " : bonne nuit." << std::endl;
}
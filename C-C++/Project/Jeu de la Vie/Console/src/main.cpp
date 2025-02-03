#include <iostream>
#include <string>
#include "../include/grille.hpp"
#include <thread> 
#include <chrono>

int main()
{
    Grille g1{12, 25};

    g1(5, 14) = '#';
    g1(5, 12) = '#';
    g1(6, 12) = '#';
    g1(6, 13) = '#';
    g1(6, 11) = '#';
    
    while(1)
    {
        std::cout << g1 << std::endl;
        g1.detectCells();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}
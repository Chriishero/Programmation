#include <iostream>
#include "../include/labyrinthe.hpp"
#include <chrono>
#include <thread>

int main()
{   
    Labyrinthe l1{10, 20};

    l1.createLabyrinthe();
    std::cout << l1 << std::endl;
    std::cout << "Le départ est à la case : " << l1.getStartCase()[0] << "," << l1.getStartCase()[1] << std::endl;
    std::cout << "La sortie est à la case : " << l1.getExitCase()[0] << "," << l1.getExitCase()[1] << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2)); // attend 2sec dans le programme

    l1.solveLabyrinthe();
    std::cout << std::endl << l1 << std::endl;

    return 0;
}

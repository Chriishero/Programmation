// DoubleRodeSimulation.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "main.h"
#include "SFML/Graphics.hpp"

sf::RenderWindow window;

int main()
{
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Double Rode Physics Simulation");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            window.clear(sf::Color::Black);
            window.display();
        }
    }
}

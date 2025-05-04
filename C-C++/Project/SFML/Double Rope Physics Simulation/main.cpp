#include <iostream>
#include "SFML/Graphics.hpp"
#include "main.h"
#include "Rode.h"

sf::RenderWindow window;

int main()
{
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Double Rode Physics Simulation");
    window.setVerticalSyncEnabled(true);

    Rode rode1(sf::Vector2f(30, 250), sf::Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 2), sf::Vector2f(5, 5), 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            window.clear(sf::Color::Black);
            
            rode1.render(window);

            window.display();
        }
    }
}

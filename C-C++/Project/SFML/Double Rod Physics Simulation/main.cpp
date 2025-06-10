#include <iostream>
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>
#include <TGUI/TGUI.hpp>
#include "main.h"
#include "World.h"

sf::RenderWindow window;

int main()
{
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Double Rode Physics Simulation");
    window.setVerticalSyncEnabled(true);
    sf::Clock deltaClock;
    Renderer renderer(window);

	tgui::GuiSFML gui(window);

    World world(9.81f, 0.0f);
    world.create();

    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        world.render(renderer);
        world.update(deltaTime);

        window.display();
    }
    return 0;
}

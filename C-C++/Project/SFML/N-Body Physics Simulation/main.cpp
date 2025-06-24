#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "main.h"
#include "Renderer.h"
#include "World.h"

sf::RenderWindow window;

int main() {
	window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "N-Body Physics Simulation");
	window.setVerticalSyncEnabled(true);
	sf::Clock deltaClock;

	tgui::GuiSFML gui(window);

	Renderer renderer(window);
	World world(1e3);
	world.create();
	world.setGui(gui);
		
	while (window.isOpen()) {
		float deltaTime = deltaClock.getElapsedTime().asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) {
			gui.handleEvent(event);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear(sf::Color::Black);

		world.update(deltaTime);
		world.render(renderer);

		gui.draw();
		window.display();
	}

	return 0;
}
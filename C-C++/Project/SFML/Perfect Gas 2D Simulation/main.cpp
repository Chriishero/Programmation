#include "main.hpp"
#include "Camera.h"

int WIN_WIDTH = 1280;
int WIN_HEIGHT = 720;
sf::RenderWindow window;

int main() {
	window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Perfect Gas 2D Simulation");
	window.setVerticalSyncEnabled(true);
	sf::Clock deltaClock;

	tgui::GuiSFML gui(window);

	Renderer renderer(window);
	Camera camera;

	World world;
	world.create();
	while (window.isOpen()) {
		float frameTime = deltaClock.getElapsedTime().asSeconds();
		std::cout << "Frame time : " << frameTime << " seconds" << std::endl;
		deltaClock.restart();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);

		//window.setView(camera.getView(window.getSize()));
		world.update(frameTime);
		world.render(renderer);

		gui.draw();
		window.display();
	}

	return (0);
}
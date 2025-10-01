#include "main.hpp"
#include "Camera.h"

int WIN_WIDTH = 1280;
int WIN_HEIGHT = 720;
sf::RenderWindow window;

int main() {
	window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Perfect Gas 2D Simulation");
	window.setVerticalSyncEnabled(true);
	sf::Clock deltaClock;

	ImGui::SFML::Init(window);

	Renderer renderer(window);
	Camera camera(1000.0f);

	World world;
	world.create();
	while (window.isOpen()) {
		float frameTime = deltaClock.getElapsedTime().asSeconds();
		//std::cout << "Frame time : " << frameTime << " seconds" << std::endl;
		deltaClock.restart();

		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed)
				window.close();
		}
		ImGui::SFML::Update(window, deltaClock.restart());
		window.clear(sf::Color::Black);

		window.setView(camera.getView(window.getSize()));
		world.update(frameTime);
		world.render(renderer);
		world.renderGui();

		ImGui::SFML::Render(window);
		window.display();
	}
	world.~World();

	return (0);
}
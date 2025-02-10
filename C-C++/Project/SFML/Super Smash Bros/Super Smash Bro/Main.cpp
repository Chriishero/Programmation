#include <SFML/Graphics.hpp>
#include <enet/enet.h>
#include "Game.h"
#include "Renderer.h"

sf::RenderWindow window;
int main()
{
	window.create(sf::VideoMode(1280, 720), "Super Smash Bros");
	sf::Clock deltaClock;
	Renderer renderer(window);
	window.setFramerateLimit(60);

	begin();
	while (window.isOpen())
	{
		float deltaTime = deltaClock.restart().asSeconds();

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			updateUI(deltaTime, event);
		}
		update(deltaTime);
		
		window.clear();

		window.setView(camera.getView(window.getSize()));
		render(renderer);
		window.setView(camera.getUIView());
		renderUI(renderer);

		window.display();
	}

	return 0;
}
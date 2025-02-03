#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "renderer.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(540, 960), "Flappy Bird");
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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				paused = !paused;
			}
		}
		update(deltaTime);

		window.clear();

		window.setView(camera.getView(window.getSize())); // définit la vue de la fenêtre
		render(renderer);

		window.setView(camera.getUIView()); // vue de l'UI
		renderUI(renderer);

		window.display();
	}

	return 0;
}
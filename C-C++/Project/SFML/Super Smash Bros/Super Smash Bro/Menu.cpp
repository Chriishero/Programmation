#include "Menu.h"
#include <algorithm>

static char text[256] = "";

Menu::Menu(sf::RenderWindow& window) : m_window(window)
{
}

void Menu::begin()
{
	for (auto const texture : Resources::textures)
	{
		std::string path = texture.first;
		if (path.starts_with("menu"))
		{
			m_texturesToDraw[path] = texture.second;
			m_texturesPosition[path] = sf::Vector2f(0.0f, 0.0f);
			m_texturesSize[path] = sf::Vector2f(0.0f, 0.0f);
			m_to_display[path] = false;
		}
	}

	menuState = true;
}

void Menu::resetTextureToDisplay()
{
	for (auto const t : m_texturesToDraw)
	{
		m_to_display[t.first] = false;
	}
}

void Menu::selectGame(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.mouseButton.button == sf::Keyboard::M)
		{
			std::cout << "multiplayer" << std::endl;
			m_multiplayerUI = true;
			m_gameUI = false;

			resetTextureToDisplay();
		}
	}
}

void Menu::character(sf::Event event)
{

}

void Menu::multiplayer(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.mouseButton.button == sf::Keyboard::C)
		{
			std::cout << "create party" << std::endl;
			m_charactersUI = true;
			m_multiplayerUI = false;

			resetTextureToDisplay();
		}
		else if (event.mouseButton.button == sf::Keyboard::J)
		{
			std::cout << "join party" << std::endl;
			m_multiplayerUI = true;
			m_gameUI = false;

			resetTextureToDisplay();
		}
	}
}

void Menu::update(float deltaTime, sf::Event event, sf::Vector2f size, sf::Vector2f position)
{
	if (m_gameUI)
	{
		m_texturesSize["menu/game-button-1.png"] = sf::Vector2f(size.x * 0.5, size.y * 0.2);
		m_texturesPosition["menu/game-button-1.png"] = sf::Vector2f(position.x - 10, position.y);
		m_to_display["menu/game-button-1.png"] = true;

		selectGame(event);
	}
	else if (m_charactersUI)
	{
		character(event);
	}
	else if (m_multiplayerUI)
	{
		m_texturesSize["menu/multiplayer-button-1.png"] = sf::Vector2f(size.x * 0.5, size.y * 0.2);
		m_texturesPosition["menu/multiplayer-button-1.png"] = sf::Vector2f(position.x, position.y - 20);
		m_to_display["menu/multiplayer-button-1.png"] = true;
		m_texturesSize["menu/multiplayer-button-2.png"] = sf::Vector2f(size.x * 0.5, size.y * 0.2);
		m_texturesPosition["menu/multiplayer-button-2.png"] = sf::Vector2f(position.x, position.y + 20);
		m_to_display["menu/multiplayer-button-2.png"] = true;

		multiplayer(event);
	}
	else
	{
		sf::RenderTexture renderTexture;
		renderTexture.create(size.x*2, size.y*2);

		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(size.x * 2, size.y * 2));
		rectangle.setPosition(position);
		rectangle.setFillColor(sf::Color::White);
		renderTexture.draw(rectangle);
		renderTexture.display();
		titleBackground = renderTexture.getTexture();

		m_texturesSize["menu/title.png"] = sf::Vector2f(size.x * 0.5, size.y * 0.5);
		m_texturesPosition["menu/title.png"] = position;
		m_to_display["menu/title.png"] = true;

		if (event.type == sf::Event::KeyReleased)
		{
			m_gameUI = true;

			resetTextureToDisplay();
		}
	}
}

void Menu::draw(Renderer& renderer)
{
	renderer.draw(titleBackground, sf::Vector2f(0.0f, 0.0f), (sf::Vector2f)titleBackground.getSize());
	for (auto const texture : m_texturesToDraw)
	{
		std::string name = texture.first;
		if (m_to_display[name])
		{
			renderer.draw(texture.second, m_texturesPosition[name], m_texturesSize[name]);
		}
	}
}

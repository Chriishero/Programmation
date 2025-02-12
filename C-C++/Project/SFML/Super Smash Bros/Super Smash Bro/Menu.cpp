#include "Menu.h"
#include <algorithm>

static char text[256] = "";
sf::Text m_hostText("host:port", font);

Menu::Menu(sf::RenderWindow& window) : m_window(window)
{
}

void Menu::begin()
{
	menuState = true;

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
	m_hostText.setFont(font);
	m_hostText.setString("host:port");
	m_hostText.setCharacterSize(45);
	m_hostText.setFillColor(sf::Color::Black);
	m_hostText.setScale(0.1, 0.2);
}

void Menu::resetTextureToDisplay()
{
	for (auto const t : m_texturesToDraw)
	{
		m_to_display[t.first] = false;
	}
}

void Menu::createInputBox()
{
	
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

void Menu::characterUI(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.mouseButton.button == sf::Keyboard::M)
		{
			character = new Character("Mario", true);
			character->begin();
			characters.push_back(character);
			m_charactersUI = false;

			resetTextureToDisplay();
			menuState = false;
		}
		else if (event.mouseButton.button == sf::Keyboard::L)
		{
			character = new Character("Link", true);
			character->begin();
			characters.push_back(character);
			m_charactersUI = false;

			resetTextureToDisplay();
			menuState = false;
		}
	}
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
			m_intputBox = false;

			resetTextureToDisplay();

			initializeServer();
		}
		else if (event.mouseButton.button == sf::Keyboard::J)
		{
			std::cout << "join party" << std::endl;
			m_charactersUI = true;
			m_multiplayerUI = false;
			m_intputBox = false;

			resetTextureToDisplay();

			joinServer(m_hostPort);
		}
		else if (event.mouseButton.button == sf::Keyboard::I)
		{
			std::cout << "input" << std::endl;
			m_intputBox = true;
		}
	}
	if(m_intputBox)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (m_keyToString.find(event.key.code) != m_keyToString.end())
			{
				m_hostPort.push_back(m_keyToString[event.key.code]);
				m_hostText.setString(m_hostPort);
				std::cout << m_keyToString[event.key.code];
			}
			else if (event.key.code == sf::Keyboard::Backspace)
			{
				m_hostPort.pop_back();
				m_hostText.setString(m_hostPort);
			}
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
		m_texturesSize["menu/character-1.png"] = sf::Vector2f(size.x * 0.6, size.y * 0.8);
		m_texturesPosition["menu/character-1.png"] = sf::Vector2f(position.x, position.y);
		m_to_display["menu/character-1.png"] = true;

		characterUI(event);
	}
	else if (m_multiplayerUI)
	{
		m_texturesSize["menu/multiplayer-button-1.png"] = sf::Vector2f(size.x * 0.5, size.y * 0.2);
		m_texturesPosition["menu/multiplayer-button-1.png"] = sf::Vector2f(position.x, position.y - 30);
		m_to_display["menu/multiplayer-button-1.png"] = true;

		if(!m_intputBox)
		{
			m_texturesSize["menu/multiplayer-inputbox-2.png"] = sf::Vector2f(size.x * 0.5, size.y * 0.1);
			m_texturesPosition["menu/multiplayer-inputbox-2.png"] = sf::Vector2f(position.x, position.y + 10);
			m_to_display["menu/multiplayer-inputbox-2.png"] = true;
			m_to_display["menu/multiplayer-inputbox-1.png"] = false;
		}
		else
		{
			m_texturesSize["menu/multiplayer-inputbox-1.png"] = sf::Vector2f(size.x * 0.5, size.y * 0.1);
			m_texturesPosition["menu/multiplayer-inputbox-1.png"] = sf::Vector2f(position.x, position.y + 10);
			m_to_display["menu/multiplayer-inputbox-1.png"] = true;
			m_to_display["menu/multiplayer-inputbox-2.png"] = false;
			m_hostText.setPosition(sf::Vector2f(position.x - m_texturesSize["menu/multiplayer-inputbox-1.png"].x/2.1, position.y + 4));
		}

		m_texturesSize["menu/multiplayer-button-2.png"] = sf::Vector2f(size.x * 0.5, size.y * 0.2);
		m_texturesPosition["menu/multiplayer-button-2.png"] = sf::Vector2f(position.x, position.y + 50);
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
	if (m_intputBox)
	{
		renderer.target.draw(m_hostText);
	}
}

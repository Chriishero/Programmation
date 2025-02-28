#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Renderer.h"
#include "Resources.h"
#include "Character.h"
#include "Map.h"
#include "Game.h"
#include <vector>
#include <string>
#include <map>

class Menu
{
public:
	Menu(sf::RenderWindow& window);

	void begin();
	void resetTextureToDisplay();
	void createInputBox();
	void selectGame(sf::Event event);
	void mapUI(sf::Event event);
	void characterUI(sf::Event event);
	void multiplayer(sf::Event event);
	void gameResultUI(sf::Event event);
	void update(float deltaTime, sf::Event event, sf::Vector2f size, sf::Vector2f position);
	void draw(Renderer& renderer);

private:
	sf::RenderWindow& m_window;

	std::map<std::string, sf::Texture> m_texturesToDraw{};
	std::map<std::string, sf::Vector2f> m_texturesPosition{};
	std::map<std::string, sf::Vector2f> m_texturesSize{};
	std::map<std::string, bool> m_to_display{};

	bool m_gameUI = false;
	bool m_multiplayerUI = false;
	bool m_intputBox = false;
	bool m_mapUI = false;
	bool m_charactersUI = false;
	bool m_inGameUI = false;
	bool m_gameResultUI = false;
	bool m_restartButton = false;

	sf::Texture titleBackground;
	std::string m_hostPort;

	sf::Vector2f m_lifeTextPosition;

    std::map<sf::Keyboard::Key, char> m_keyToString = {
        {sf::Keyboard::Numpad0, '0'},
        {sf::Keyboard::Numpad1, '1'},
        {sf::Keyboard::Numpad2, '2'},
        {sf::Keyboard::Numpad3, '3'},
        {sf::Keyboard::Numpad4, '4'},
        {sf::Keyboard::Numpad5, '5'},
        {sf::Keyboard::Numpad6, '6'},
        {sf::Keyboard::Numpad7, '7'},
        {sf::Keyboard::Numpad8, '8'},
        {sf::Keyboard::Numpad9, '9'},
        {sf::Keyboard::Period, '.'},
        {sf::Keyboard::Semicolon, ':'}};

};


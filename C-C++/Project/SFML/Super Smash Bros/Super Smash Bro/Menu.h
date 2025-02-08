#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Renderer.h"
#include "Resources.h"
#include "Character.h"
#include "Game.h"
#include <vector>
#include <string>
#include <map>

class Menu
{
public:
	Menu();

	void begin();
	void character();
	void multiplayer();
	void update(float deltaTime, sf::Vector2f size);
	void draw(Renderer& renderer);

private:
	std::map<std::string, sf::Texture> m_texturesToDraw{};
	std::map<std::string, sf::Vector2f> m_texturesPosition{};
	std::map<std::string, sf::Vector2f> m_texturesSize{};
	std::map<std::string, bool> m_to_display{};

	bool m_charactersUI = false;
	bool m_multiplayerUI = false;
};


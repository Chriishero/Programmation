#include "Menu.h"
#include <algorithm>

Menu::Menu()
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

	title = false;
}

void Menu::character()
{
}

void Menu::multiplayer()
{
}

void Menu::update(float deltaTime, sf::Vector2f size)
{
	if (m_charactersUI)
	{
		character();
	}
	else if (m_multiplayerUI)
	{
		multiplayer();
	}
	else
	{
		m_texturesSize["menu/title.png"] = size;
		m_to_display["menu/title.png"] = true;
	}
}

void Menu::draw(Renderer& renderer)
{
	for (auto const texture : m_texturesToDraw)
	{
		std::string name = texture.first;
		if (m_to_display[name])
		{
			renderer.draw(texture.second, m_texturesPosition[name], m_texturesSize[name]);
		}
	}
}

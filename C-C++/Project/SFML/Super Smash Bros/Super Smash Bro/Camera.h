#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(float zoomLevel = 5.0f);
	sf::Vector2f getm_viewSize();
	sf::View getView(sf::Vector2u windowSize);
	sf::View getUIView();

	float getm_zoomLevel();
	sf::Vector2f getm_position();

private:
	float m_zoomLevel;
	sf::Vector2f m_position;
	sf::Vector2f m_viewSize{};
};


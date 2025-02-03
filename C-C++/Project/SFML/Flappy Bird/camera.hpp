#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(float zoomLevel = 5.0f);
	sf::Vector2f getViewSize();
	sf::View getView(sf::Vector2u windowSize);
	sf::View getUIView();

	float getzoomLevel();
	sf::Vector2f getposition();

private:
	float m_zoomLevel;
	sf::Vector2f m_position;
	sf::Vector2f m_viewSize{};
};
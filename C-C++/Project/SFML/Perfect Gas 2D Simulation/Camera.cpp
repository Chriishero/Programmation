#include "Camera.h"

Camera::Camera(float zoomLevel) : m_zoomLevel(zoomLevel)
{}

sf::View Camera::getView(sf::Vector2u windowSize)
{
	float		 aspectRatio;
	sf::Vector2f size;

	aspectRatio = (float)windowSize.x / (float)windowSize.y;
	if (aspectRatio < 1.0f) {
		size.x = m_zoomLevel;
		size.y = m_zoomLevel / aspectRatio;
	} 
	else {
		size.x = m_zoomLevel * aspectRatio;
		size.y = m_zoomLevel;
	}

	return (sf::View(sf::Vector2f(WIN_HEIGHT / 2.0f, WIN_WIDTH / 2.0f), size));
}



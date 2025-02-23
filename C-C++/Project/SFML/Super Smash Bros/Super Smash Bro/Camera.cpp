#include "Camera.h"

Camera::Camera(float zoomLevel) : m_zoomLevel(zoomLevel)
{
}

sf::Vector2f Camera::getm_viewSize()
{
	return m_viewSize;
}

sf::View Camera::getView(sf::Vector2u windowSize)
{
	float aspect = (float)windowSize.x / (float)windowSize.y; // calcul l'aspect ratio
	if (aspect < 1.0f) // si la fen�tre est plus haute que large
	{
		m_viewSize = sf::Vector2f(m_zoomLevel, m_zoomLevel / aspect);
		// largeur = zoomLevel, hauteur = agrandit verticalement la vue pour �viter les d�formation
	}
	else
	{
		m_viewSize = sf::Vector2f(m_zoomLevel / aspect, m_zoomLevel);
	}
	return sf::View(m_position, m_viewSize);
	// m_position : centre de la vue
	// m_viewSize : dimension de la vue calcul�, �tendu visible de la sc�ne
}

sf::View Camera::getUIView()
{
	float aspect = (float)m_viewSize.x / (float)m_viewSize.y; // calcul l'aspect ratio
	m_viewSize = sf::Vector2f(100.0f, 100.0f / aspect);
	// largeur = 100.0f, hauteur = ajust� en fonction de l'aspect ratio

	return sf::View(sf::Vector2f(), m_viewSize);
	// sf::Vector2f() : positon centrale de la vue (0,0)
	// m_viewSize : taille de la vue mise � jour
}

float Camera::getm_zoomLevel()
{
	return m_zoomLevel;
}

sf::Vector2f Camera::getm_position()
{
	return m_position;
}

void Camera::setm_position(sf::Vector2f pos)
{
	m_position = pos;
}

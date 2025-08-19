#pragma once

#include "main.hpp"

class Camera
{
	public:
		Camera(float zoomLevel = 1.0f);

		sf::View getView(sf::Vector2u windowSize);

	private:
		float m_zoomLevel;
};


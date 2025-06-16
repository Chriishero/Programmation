#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"

class Body {
public:
	Body(sf::Vector2f position, sf::Vector2f size, sf::Vector2f velocity, float weight);

	void begin();
	void update(float deltaTime);
	void render(Renderer& renderer);

private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Vector2f m_velocity;
	float m_weight;

	sf::Vector2f m_acceleration;
};
#pragma once
#include "SFML/Graphics.hpp"

class Rode
{
public:
	Rode(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity, float weight);

	void render(sf::RenderWindow &window);
private:
	sf::RectangleShape m_rodeShape;
	sf::CircleShape m_jointShape;

	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_weight;
};


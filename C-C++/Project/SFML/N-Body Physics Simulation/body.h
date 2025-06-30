#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"

class Body {
public:
	Body(float size, sf::Vector2f position, sf::Vector2f velocity, float weight);

	void begin();
	void update(float deltaTime);
	void render(Renderer& renderer);

	float getm_size();
	sf::Vector2f getm_position();
	sf::Vector2f getm_velocity();
	sf::Vector2f getm_acceleration();
	float getm_weight();

	void setm_size(float size);
	void setm_position(sf::Vector2f position);
	void setm_velocity(sf::Vector2f velocity);
	void setm_acceleration(sf::Vector2f acceleration);
	void setm_weight(float weight);

private:
	sf::Vector2f m_position;
	float m_size;
	sf::Vector2f m_velocity;
	float m_weight;

	sf::Vector2f m_acceleration;

	sf::CircleShape m_bodyShape{};
	sf::RenderTexture m_bodyRenderTexture{};
	sf::Texture m_bodyTexture{};
};
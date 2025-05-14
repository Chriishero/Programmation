#pragma once
#include "SFML/Graphics.hpp"
#include "Renderer.h"

class Rode
{
public:
	Rode(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity, float weight);

	void motion();
	void update(float deltaTime);
	void draw(Renderer& renderer);

	sf::Vector2f getm_position();
	sf::Vector2f getm_size();
	sf::Vector2f getm_massPosition();
	sf::Vector2f getm_massSize();

private:
	sf::RenderTexture m_renderJointToDraw{};
	sf::RenderTexture m_renderRodToDraw{};
	sf::RenderTexture m_renderMassToDraw{};
	sf::Texture m_jointToDraw{};
	sf::Texture m_rodToDraw{};
	sf::Texture m_MassToDraw{};
	sf::RectangleShape m_rodeShape;
	sf::CircleShape m_jointShape;
	sf::CircleShape m_MassShape;

	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_massSize;
	sf::Vector2f m_massPosition;
	float m_weight;
};
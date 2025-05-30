#pragma once
#include "SFML/Graphics.hpp"
#include "Renderer.h"

class Rode
{
public:
	Rode(sf::Vector2f size, sf::Vector2f position, float angle, sf::Vector2f velocity, float weight);

	void motion();
	void update(float deltaTime);
	void draw(Renderer& renderer);

	float getm_energy();
	sf::Vector2f getm_position();
	sf::Vector2f getm_size();
	sf::Vector2f getm_massPosition();
	sf::Vector2f getm_massOrigin();
	sf::Vector2f getm_massSize();
	float getm_angle();
	float getm_angularVelocity();
	float getm_angularAcceleration();
	float getm_weight();

	void setm_position(sf::Vector2f position);
	void setm_massPosition(sf::Vector2f position);
	void setm_jointOrigin(sf::Vector2f origin);
	void setm_jointPosition(sf::Vector2f position);
	void setm_angle(float angle);
	void setm_angularVelocity(float angularVelocity);
	void setm_angularAcceleration(float angularAcceleration);
private:
	float m_potentialEnergy = 0.0f;
	float m_kineticEnergy = 0.0f;
	float m_energy = 0.0f;

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
	float m_angle;
	float m_angularVelocity = 1.0f;
	float m_angularAcceleration = 1.0f;

	sf::Vector2f m_jointPosition;
	sf::Vector2f m_jointOrigin;
	sf::Vector2f m_rodOrigin;
	sf::Vector2f m_velocity;
	sf::Vector2f m_massSize;
	sf::Vector2f m_massOrigin;
	sf::Vector2f m_massPosition;
	float m_weight;
};
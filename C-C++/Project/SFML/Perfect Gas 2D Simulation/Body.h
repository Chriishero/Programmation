#pragma once

#include "main.hpp"

class Shape;

class Body // C'EST UNIQUEMENT LE CORPS QUI A POS VEL ET ACC DE MODIFIER ET QUI LES CONTIENT
{
	public:
		Body();
		~Body();

		void setShape(Shape *shape);
		const Shape& getShape() const;

		void setSize(const sf::Vector2f size);
		const sf::Vector2f getSize() const;

		void setPosition(const sf::Vector2f position);
		const sf::Vector2f getPosition() const;

		void setVelocity(const sf::Vector2f velocity);
		const sf::Vector2f getVelocity() const;

		void setAcceleration(const sf::Vector2f acceleration);
		const sf::Vector2f getAcceleration() const;

		const std::vector<sf::Vector2f> getBoundaries();
		
	private:
		Shape* m_shape;
		sf::Vector2f m_size;
		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
		sf::Vector2f m_acceleration;
};


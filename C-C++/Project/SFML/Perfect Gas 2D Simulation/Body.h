#pragma once

#include "main.hpp"

class Shape;

class Body // JE VEUX FAIRE EN SORTE DE STOCKER LA POSITION DE TOUS LES PIXELS OCCUPÉ PAR LE CORPS
{
	public:
		Body();

		void setShape(const Shape& shape);
		const Shape& getShape() const;

		void setSize(const float size);
		const float getSize() const;

		void setPosition(const sf::Vector2f position);
		const sf::Vector2f getPosition() const;
		
	private:
		Shape* m_shape;
		float m_size;
		sf::Vector2f m_position;
};


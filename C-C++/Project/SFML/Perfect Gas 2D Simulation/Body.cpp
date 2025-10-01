#include "Body.h"

Body::Body()
{}

Body::~Body()
{}

void Body::setShape(Shape *shape)
{
	m_shape = shape;
}

const Shape& Body::getShape() const
{
	return *m_shape;
}

void Body::setSize(const sf::Vector2f size)
{
	m_size = size;
}

const sf::Vector2f Body::getSize() const
{
	if (m_shape->getType() == Shape::Type::Circle)
		return m_size / 2.0f;
	return m_size;
}

void Body::setPosition(const sf::Vector2f position)
{
	m_position = position;
}

const sf::Vector2f Body::getPosition() const
{
	return m_position;
}

void Body::setVelocity(const sf::Vector2f velocity)
{
	m_velocity = velocity;
}

const sf::Vector2f Body::getVelocity() const
{
	return m_velocity;
}

void Body::setAcceleration(const sf::Vector2f acceleration)
{
	m_acceleration = acceleration;
}

const sf::Vector2f Body::getAcceleration() const
{
	return m_acceleration;
}

const std::vector<sf::Vector2f> Body::getBoundaries()
{
	std::vector<sf::Vector2f> boundaries{};
	if (m_shape->getType() == Shape::Type::Circle)
	{
;		for (int a = 1; a < 360; a++)
		{
			float angle = a * M_PI / 180.0f;
			sf::Vector2f pixelPosition = { m_size.x * cos(angle) + m_position.x, m_size.y * sin(angle) + m_position.y };
			boundaries.push_back(pixelPosition);
		}
	}
	if (m_shape->getType() == Shape::Type::Rectangle)
	{
		float left_edge = m_position.x;
		float right_edge = m_position.x + m_size.x - 1;
		float top_edge = m_position.y;
		float bottom_edge = m_position.y + m_size.y - 1;

		for (float x = left_edge; x <= right_edge; x++)
		{
			boundaries.push_back({ x, top_edge });
			boundaries.push_back({ x, bottom_edge });
		}
		for (float y = top_edge; y <= bottom_edge; y++)
		{
			boundaries.push_back({ left_edge, y });
			boundaries.push_back({ right_edge, y });
		}
	}
	return (boundaries);
}


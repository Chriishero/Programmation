#include "Body.h"

Body::Body()
{}

void Body::setShape(const Shape& shape)
{
	*m_shape = shape;
}

const Shape& Body::getShape() const
{
	return *m_shape;
}

void Body::setSize(const float size)
{
	m_size = size;
}

const float Body::getSize() const
{
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


#include "Body.h"

Body::Body(float size, sf::Vector2f position, sf::Vector2f velocity, float weight) :
		m_size(size), m_position(position), m_velocity(velocity), m_weight(weight){

}

void Body::begin() {
	m_bodyShape.setRadius(m_size);
	m_bodyShape.setPosition(0, 0);
	m_bodyShape.setFillColor(sf::Color::White);

	m_bodyRenderTexture.create(m_bodyShape.getRadius() * 2, m_bodyShape.getRadius() * 2);
	m_bodyRenderTexture.clear();
	m_bodyRenderTexture.draw(m_bodyShape);
	m_bodyRenderTexture.display();

	m_bodyTexture = m_bodyRenderTexture.getTexture();
}

void Body::update(float deltaTime) {
	m_velocity += m_acceleration * deltaTime;
	m_position += m_velocity * deltaTime;
	m_position += m_velocity * deltaTime;
}

void Body::render(Renderer& renderer) {
	renderer.draw(m_bodyTexture, m_position, sf::Vector2f(m_size, m_size));
}

sf::Vector2f Body::getm_position()
{
	return m_position;
}

sf::Vector2f Body::getm_velocity()
{
	return m_velocity;
}

sf::Vector2f Body::getm_acceleration()
{
	return m_acceleration;
}

float Body::getm_weight()
{
	return m_weight;
}

void Body::setm_size(float size)
{
	m_size = size;
}

void Body::setm_position(sf::Vector2f position)
{
	m_position = position;
}

void Body::setm_velocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

void Body::setm_acceleration(sf::Vector2f acceleration)
{
	m_acceleration = acceleration;
}

void Body::setm_weight(float weight)
{
	m_weight = weight;
}

float Body::getm_size()
{
	return m_size;
}

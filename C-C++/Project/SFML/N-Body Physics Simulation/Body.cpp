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

}

void Body::render(Renderer& renderer) {
	renderer.draw(m_bodyTexture, m_position, sf::Vector2f(m_size, m_size));
}

sf::Vector2f Body::getm_position()
{
	return m_position;
}

float Body::getm_size()
{
	return m_size;
}

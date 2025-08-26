#include "Renderer.h"

Renderer::Renderer(sf::RenderTarget& target) : m_target(&target)
{}

void Renderer::draw(const sf::Texture& texture, const sf::Vector2f position, const sf::Vector2f size, std::optional<sf::Vector2f> origin, float angle)
{
	m_sprite.setTexture(texture, true);
	m_sprite.setOrigin(origin.value_or(sf::Vector2f(0, 0))); // origine par défaut à (0, 0) si nullopt
	m_sprite.setPosition(position);
	m_sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
	m_sprite.setRotation(angle);

	m_target->draw(m_sprite);
}

void Renderer::drawVertexArray(const sf::VertexArray& vertexArray)
{
	m_target->draw(vertexArray);
}

sf::RenderTarget& Renderer::getm_target()
{
	return (*m_target);
}

void Renderer::setm_target(sf::RenderTarget& target)
{
	m_target = &target;
}

#include "Renderer.h"

Renderer::Renderer(sf::RenderTarget& target) : target(target)
{
}

void Renderer::draw(const sf::Texture& texture, const sf::Vector2f position, const sf::Vector2f size, std::optional<sf::Vector2f> origin, float angle)
{
	m_sprite.setTexture(texture, true);
	m_sprite.setOrigin((origin.has_value()) ? origin.value() : (sf::Vector2f)texture.getSize() / 2.0f);
	m_sprite.setPosition(position);
	m_sprite.setRotation(angle);
	m_sprite.setScale(sf::Vector2f(size.x / texture.getSize().x, size.y / texture.getSize().y));
	target.draw(m_sprite);
}

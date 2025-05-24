#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Renderer
{
public:
	Renderer(sf::RenderTarget& target);

	void draw(const sf::Texture& texture, const sf::Vector2f position, const sf::Vector2f size, std::optional<sf::Vector2f> origin = std::nullopt, float angle = 0.0f);

	sf::RenderTarget& target;

private:
	sf::Sprite m_sprite{};
};


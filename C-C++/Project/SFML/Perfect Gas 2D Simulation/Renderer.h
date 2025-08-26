#pragma once

#include "main.hpp"

class Renderer
{
	public:
		Renderer(sf::RenderTarget& target);

		void draw(const sf::Texture& texture, const sf::Vector2f position, const sf::Vector2f size,
			std::optional<sf::Vector2f> origin = std::nullopt, float angle = 0.0f);
		void drawVertexArray(const sf::VertexArray& vertexArray);

		sf::RenderTarget& getm_target();
		
		void setm_target(sf::RenderTarget& target);

	private:
		sf::RenderTarget* m_target;
		sf::Sprite m_sprite;
};


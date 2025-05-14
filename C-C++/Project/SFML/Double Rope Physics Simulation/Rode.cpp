#include "Rode.h"

Rode::Rode(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity, float weight)
    : m_size(size), m_position(position), m_velocity(velocity), m_weight(weight)
{
    auto setCircleToDraw = [&](sf::CircleShape& shape, sf::RenderTexture& render, sf::Texture& texture) {
        shape.setRadius(size.x);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(size.x, size.x);
        shape.setPosition({ size.x, size.x }); 

        render.create(size.x * 2, size.x * 2);
        render.clear(sf::Color::Transparent);
        render.draw(shape);
        render.display();
        texture = render.getTexture();
    };

    // Joint
    setCircleToDraw(m_jointShape, m_renderJointToDraw, m_jointToDraw);

    // Rod
    m_rodeShape.setSize(size);
    m_rodeShape.setFillColor(sf::Color::White);
    m_rodeShape.setPosition({ 0, 0 }); // dans la texture
    m_renderRodToDraw.create(size.x, size.y);
    m_renderRodToDraw.clear(sf::Color::Transparent);
    m_renderRodToDraw.draw(m_rodeShape);
    m_renderRodToDraw.display();
    m_rodToDraw = m_renderRodToDraw.getTexture();

    // Mass
    setCircleToDraw(m_MassShape, m_renderMassToDraw, m_MassToDraw);
}


void Rode::motion()
{
}

void Rode::update(float deltaTime)
{
}

void Rode::draw(Renderer& renderer) {
    renderer.draw(m_jointToDraw, sf::Vector2f(m_position.x, m_position.y - m_size.y / 2), sf::Vector2f(m_size.x * 1.5, m_size.x * 1.5));
    renderer.draw(m_rodToDraw, m_position, m_size);
    renderer.draw(m_MassToDraw, sf::Vector2f(m_position.x, m_position.y + m_size.y / 2), sf::Vector2f(m_size.x * 2, m_size.x * 2));
}

sf::Vector2f Rode::getm_position()
{
    return m_position;
}
sf::Vector2f Rode::getm_size() {
    return m_size;
}

sf::Vector2f Rode::getm_massPosition()
{
    return m_massPosition;
}

sf::Vector2f Rode::getm_massSize()
{
    return m_massSize;
}

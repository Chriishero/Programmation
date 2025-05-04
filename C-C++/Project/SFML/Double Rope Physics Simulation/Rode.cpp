#include "Rode.h"

Rode::Rode(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity, float weight) : m_size(size), m_position(position), m_velocity(velocity), m_weight(weight)
{
    m_rodeShape.setSize(size);
    m_rodeShape.setFillColor(sf::Color::White);
    m_rodeShape.setPosition(position);
    m_jointShape.setRadius(size.x);
    m_jointShape.setFillColor(sf::Color::White);
    m_jointShape.setPosition(sf::Vector2f(position.x - size.x/2, position.y - size.x/2));
}

void Rode::render(sf::RenderWindow &window) {
    window.draw(m_rodeShape);
    window.draw(m_jointShape);
}

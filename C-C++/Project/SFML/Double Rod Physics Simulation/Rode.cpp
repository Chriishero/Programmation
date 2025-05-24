#include "Rode.h"
#include <iostream>

Rode::Rode(sf::Vector2f size, sf::Vector2f position, float angle, sf::Vector2f velocity, float weight)
    : m_size(size), m_position(position), m_angle(angle), m_velocity(velocity), m_weight(weight)
{
    auto setCircleToDraw = [&](sf::CircleShape& shape, sf::RenderTexture& render, sf::Texture& texture) {
        shape.setRadius(size.x);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(size.x, size.y);
        shape.setPosition(size.x, size.y);

        render.create(shape.getRadius()*2, shape.getRadius() * 2);
        render.clear(sf::Color::Cyan);
        render.draw(shape);
        render.display();
        texture = render.getTexture();
    };

    // Joint
    setCircleToDraw(m_jointShape, m_renderJointToDraw, m_jointToDraw);

    // Rod
    m_rodeShape.setSize(size);
    m_rodeShape.setFillColor(sf::Color::White);
    m_rodeShape.setOrigin(0, 0);
    m_rodeShape.setPosition(0, 0);
    m_rodOrigin = sf::Vector2f(m_size.x / 2.0f, 0.0f);

    m_renderRodToDraw.create(size.x, size.y);
    m_renderRodToDraw.clear(sf::Color::Cyan);
    m_renderRodToDraw.draw(m_rodeShape);
    m_renderRodToDraw.display();
    m_rodToDraw = m_renderRodToDraw.getTexture();

    // Mass
    setCircleToDraw(m_MassShape, m_renderMassToDraw, m_MassToDraw);
    //m_massPosition = sf::Vector2f(m_position.x, m_position.y + m_size.y / 2);
    //m_massPosition = sf::Vector2f(m_size.y * sin(m_angle), -m_size.y * cos(m_angle));
}



void Rode::motion()
{
}

void Rode::update(float deltaTime)
{
    m_massOrigin = sf::Vector2f(-m_position.x + m_jointShape.getRadius() * 0.75f, -m_position.y + m_size.y / 2.0f + m_jointShape.getRadius() * 0.75f);
    m_angle += 10.0f;
    m_massPosition = sf::Vector2f(-m_size.y * sin(m_angle * (3.14f / 180)),m_size.y * cos(m_angle * (3.14f / 180)));
}

void Rode::draw(Renderer& renderer) {
    std::cout << m_angle << std::endl;
    renderer.draw(m_jointToDraw, sf::Vector2f(m_position.x, m_position.y - m_size.y / 2.0f), sf::Vector2f(m_jointShape.getRadius() * 1.5f, m_jointShape.getRadius() * 1.5f));
    renderer.draw(m_rodToDraw, sf::Vector2f(m_position.x, m_position.y - m_size.y / 2.0f), (sf::Vector2f)m_rodToDraw.getSize(), m_rodOrigin, m_angle);
    renderer.draw(m_MassToDraw, m_massPosition, sf::Vector2f(m_size.x * 2, m_size.x * 2), m_massOrigin);
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

void Rode::setm_position(sf::Vector2f position)
{
    m_position = position;
}

void Rode::setm_massPosition(sf::Vector2f position)
{
    m_massPosition = position;
}

void Rode::setm_jointOrigin(sf::Vector2f origin)
{
    m_jointOrigin = origin;
}

void Rode::setm_jointPosition(sf::Vector2f position)
{
    m_jointPosition = position;
}

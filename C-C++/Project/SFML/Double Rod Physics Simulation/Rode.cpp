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
    m_jointPosition = sf::Vector2f(m_position.x, m_position.y - m_size.y / 2.0f);

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
    m_massOrigin = sf::Vector2f(-m_jointPosition.x + m_jointShape.getRadius() * 0.75f, -m_jointPosition.y + m_jointShape.getRadius() * 0.75f);
    m_angle += 5.0f;
    m_massPosition = sf::Vector2f(-m_size.y * sin(m_angle * (3.14f / 180)),m_size.y * cos(m_angle * (3.14f / 180)));
}

void Rode::draw(Renderer& renderer) {
    renderer.draw(m_jointToDraw, m_jointPosition, sf::Vector2f(m_jointShape.getRadius() * 1.5f, m_jointShape.getRadius() * 1.5f));
    renderer.draw(m_rodToDraw, m_jointPosition, (sf::Vector2f)m_rodToDraw.getSize(), m_rodOrigin, m_angle);
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

sf::Vector2f Rode::getm_massOrigin()
{
    return m_massOrigin;
}

sf::Vector2f Rode::getm_massSize()
{
    return m_massSize;
}

float Rode::getm_angle()
{
    return m_angle;
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

void Rode::setm_angle(float angle)
{
    m_angle = angle;
}

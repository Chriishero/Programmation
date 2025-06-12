#include "Rode.h"
#include <iostream>
#include <cmath>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

Rode::Rode(sf::Vector2f size, sf::Vector2f position, float angle, float angularVelocity, float weight)
    : m_size(size), m_position(position), m_angle(angle), m_angularVelocity(angularVelocity), m_weight(weight)
{
}
void Rode::begin() {
    m_angle = m_angle * (M_PI / 180.0f);
    auto setCircleToDraw = [&](sf::CircleShape& shape, sf::RenderTexture& render, sf::Texture& texture) {
        shape.setRadius(m_size.x);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(m_size.x, m_size.y);
        shape.setPosition(m_size.x, m_size.y);

        render.create(shape.getRadius() * 2, shape.getRadius() * 2);
        render.clear(sf::Color::Cyan);
        render.draw(shape);
        render.display();
        texture = render.getTexture();
        };

    // Joint
    setCircleToDraw(m_jointShape, m_renderJointToDraw, m_jointToDraw);
    m_jointPosition = sf::Vector2f(m_position.x, m_position.y - m_size.y / 2.0f);

    // Rod
    m_rodeShape.setSize(m_size);
    m_rodeShape.setFillColor(sf::Color::White);
    m_rodeShape.setOrigin(0, 0);
    m_rodeShape.setPosition(0, 0);
    m_rodOrigin = sf::Vector2f(m_size.x / 2.0f, 0.0f);

    m_renderRodToDraw.create(m_size.x, m_size.y);
    m_renderRodToDraw.clear(sf::Color::Cyan);
    m_renderRodToDraw.draw(m_rodeShape);
    m_renderRodToDraw.display();
    m_rodToDraw = m_renderRodToDraw.getTexture();

    // Mass
    setCircleToDraw(m_MassShape, m_renderMassToDraw, m_MassToDraw);
    //m_massPosition = sf::Vector2f(m_position.x, m_position.y + m_size.y / 2);
    //m_massPosition = sf::Vector2f(m_size.y * sin(m_angle), -m_size.y * cos(m_angle));
}


void Rode::motion(float deltaTime)
{
    m_energy = m_kineticEnergy + m_potentialEnergy;

    m_angularVelocity += m_angularAcceleration * deltaTime;
	m_angle += m_angularVelocity * deltaTime;

    while (m_angle >= 2 * M_PI) m_angle -= 2 * M_PI;
    while(m_angle < 0) m_angle += 2 * M_PI;
}

void Rode::update(float deltaTime)
{
    motion(deltaTime);
    m_massOrigin = sf::Vector2f(-m_jointPosition.x + m_jointShape.getRadius() * 0.75f, -m_jointPosition.y + m_jointShape.getRadius() * 0.75f);
    m_massPosition = sf::Vector2f(-m_size.y * sin(m_angle),m_size.y * cos(m_angle));
}

void Rode::draw(Renderer& renderer) {
    renderer.draw(m_jointToDraw, m_jointPosition, sf::Vector2f(m_jointShape.getRadius() * 1.5f, m_jointShape.getRadius() * 1.5f));
    renderer.draw(m_rodToDraw, m_jointPosition, (sf::Vector2f)m_rodToDraw.getSize(), m_rodOrigin, m_angle * (180.0f / M_PI));
    renderer.draw(m_MassToDraw, m_massPosition, sf::Vector2f(m_size.x * 2, m_size.x * 2), m_massOrigin);
}

float Rode::getm_energy()
{
    return m_energy;
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

double Rode::getm_angularVelocity()
{
    return m_angularVelocity;
}

double Rode::getm_angularAcceleration()
{
    return m_angularAcceleration;
}

float Rode::getm_weight()
{
	return m_weight;
}

void Rode::setm_energy(float energy)
{
    m_energy = energy;
}

void Rode::setm_kineticEnergy(float kineticEnergy)
{
	m_kineticEnergy = kineticEnergy;    
}

void Rode::setm_potentialEnergy(float potentialEnergy)
{
	m_potentialEnergy = potentialEnergy;
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

void Rode::setm_size(sf::Vector2f size)
{
    m_size = size;
}

void Rode::setm_angle(float angle)
{
    m_angle = angle;
}

void Rode::setm_weight(float w)
{
    m_weight = w;
}

void Rode::setm_angularVelocity(float angularVelocity)
{
    m_angularVelocity = angularVelocity;
}

void Rode::setm_angularAcceleration(float angularAcceleration)
{
    m_angularAcceleration = angularAcceleration;
}

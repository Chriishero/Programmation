#include "World.h"

World::World()
{
}

void World::create()
{
	m_nMolecules = 100;
	m_volume = 1.0f; // mètre cube
	m_temperature = 300.0f; // Kelvin

	m_gas = new Gas(m_nMolecules, m_volume, m_temperature);
	m_gas->create();

	createContainer();
}

void World::createContainer()
{
	m_containerVertices.setPrimitiveType(sf::LineStrip);
	m_containerVertices.resize(5); // 4 coins + 1 pour fermer le rectangle

	m_containerVertices[0].position = sf::Vector2f(0.0f, 0.0f);
	m_containerVertices[1].position = sf::Vector2f(WIN_WIDTH, 0.0f);
	m_containerVertices[2].position = sf::Vector2f(WIN_WIDTH, WIN_HEIGHT);
	m_containerVertices[3].position = sf::Vector2f(0.0f, WIN_HEIGHT);
	m_containerVertices[4].position = sf::Vector2f(0.0f, 0.0f);

	m_containerVertices[0].color = sf::Color::White;
	m_containerVertices[1].color = sf::Color::White;
	m_containerVertices[2].color = sf::Color::White;
	m_containerVertices[3].color = sf::Color::White;
	m_containerVertices[4].color = sf::Color::White;
}

void World::update(float deltaTime)
{
	m_gas->update(deltaTime);
	m_gas->updateGui();
}

void World::render(Renderer& renderer)
{
	renderer.drawVertexArray(m_containerVertices);
	m_gas->render(renderer);
}

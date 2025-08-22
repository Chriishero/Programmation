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
}

void World::update(float deltaTime)
{
	m_gas->update(deltaTime);
	m_gas->updateGui();
}

void World::render(Renderer& renderer)
{
	m_gas->render(renderer);
}

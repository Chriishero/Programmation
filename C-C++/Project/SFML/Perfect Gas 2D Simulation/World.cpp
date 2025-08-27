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
	m_container.vertices.setPrimitiveType(sf::LineStrip);
	m_container.vertices.resize(5); // 4 coins + 1 pour fermer le rectangle

	// Position des coins du conteneurs
	m_container.vertices[0].position = sf::Vector2f(0.0f, 0.0f);
	m_container.vertices[1].position = sf::Vector2f(WIN_WIDTH, 0.0f);
	m_container.vertices[2].position = sf::Vector2f(WIN_WIDTH, WIN_HEIGHT);
	m_container.vertices[3].position = sf::Vector2f(0.0f, WIN_HEIGHT);
	m_container.vertices[4].position = sf::Vector2f(0.0f, 0.0f);

	// Couleur de la ligne reliant les coins
	m_container.vertices[0].color = sf::Color::White;
	m_container.vertices[1].color = sf::Color::White;
	m_container.vertices[2].color = sf::Color::White;
	m_container.vertices[3].color = sf::Color::White;
	m_container.vertices[4].color = sf::Color::White;

	// Épaisseur des lignes (pixel)
	m_container.outlineThickness = 1.0f;
}

void World::update(float deltaTime)
{	m_gas->update(deltaTime * m_timeScale);
}

void World::render(Renderer& renderer)
{
	// World
	renderer.drawVertexArray(m_container.vertices);

	// Gas
	m_gas->render(renderer);
}

void World::renderGui()
{
	if (ImGui::CollapsingHeader("World Settings"))
	{
		ImGui::SliderFloat("Time Scale", &m_timeScale, 0.0f, 100.0f);
	}
	m_gas->renderGui();
}

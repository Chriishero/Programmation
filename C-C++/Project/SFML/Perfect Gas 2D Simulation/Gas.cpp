#include "Gas.h"

Gas::Gas(float nMolecules, float volume, float temperature) 
	: m_nMolecules(nMolecules), m_volume(volume), m_temperature(temperature)
{}

void Gas::begin()
{
	std::random_device gen;
	for (int i = 0; i < m_nMolecules; i++)
	{
		// Random Generator
		std::uniform_int_distribution xPosRNG(0, WIN_WIDTH);
		std::uniform_int_distribution yPosRNG(0, WIN_HEIGHT);
		std::uniform_int_distribution xVelRNG(-500, 500);
		std::uniform_int_distribution yVelRNG(-500, 500);

		// Shape, RenderTexture, Texture
		m_molecule = new Molecule;
		m_molecule->shape.setPosition({ 0, 0 });
		m_molecule->shape.setRadius(20.0f);
		m_molecule->shape.setFillColor(sf::Color::White);

		m_molecule->renderTexture.create(m_molecule->shape.getGlobalBounds().width,
										 m_molecule->shape.getGlobalBounds().height);
		m_molecule->renderTexture.clear(sf::Color::Transparent);
		m_molecule->renderTexture.draw(m_molecule->shape);
		m_molecule->renderTexture.display();

		m_molecule->texture = m_molecule->renderTexture.getTexture();

		// Initial Position, size
		m_molecule->position = sf::Vector2f(xPosRNG(gen), yPosRNG(gen));
		m_molecule->size = sf::Vector2f(m_molecule->shape.getGlobalBounds().width,
										m_molecule->shape.getGlobalBounds().height);

		// Initial Velocity
		m_molecule->velocity = sf::Vector2f(xVelRNG(gen), yVelRNG(gen));

		m_moleculeList.push_back(m_molecule);
	}
}

void Gas::update(float deltaTime)
{
	for (auto& molecule : m_moleculeList)
	{
		molecule->position += deltaTime * molecule->velocity;
	}
}

void Gas::render(Renderer& renderer)
{
	for (auto& molecule : m_moleculeList)
	{
		renderer.draw(molecule->texture, molecule->position, molecule->size); 
		//printf("Molecule position : (%f, %f)\n", molecule->position.x, molecule->position.y);
	}
}

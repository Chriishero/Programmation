#include "World.h"

World::World()
{}

World::~World()
{}

void World::create()
{
	m_nMolecules = 2;
	m_volume = 1.0f; // mètre cube
	m_temperature = 300.0f; // Kelvin

	m_gas = new Gas(m_nMolecules, m_volume, m_temperature);
	m_gas->create();
	createContainer();
	
	m_physics = new Physics(m_gas->getMoleculeBodyList(), m_containerBody);
}

void World::reload()
{
	m_gas->destroy();
	m_gas->create();

	delete m_physics;
	delete m_containerBody;

	createContainer();
	m_physics = new Physics(m_gas->getMoleculeBodyList(), m_containerBody);
}

void World::createContainer()
{
	// Taille du conteneur
	m_containerSize = { (float)WIN_WIDTH, (float)WIN_HEIGHT };

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

	// Création du corps physique du conteneur
	m_containerBody = new Body();
	m_containerShape = new Shape();
	m_containerShape->setType(Shape::Type::Rectangle);
	m_containerBody->setShape(m_containerShape);
	m_containerBody->setPosition(m_container.vertices[0].position);
	m_containerBody->setSize(m_containerSize);
	printf("%d", m_containerBody->getSize().x);
	/*
	printf("Container position : (%f, %f)\n", m_container.vertices[0].position.x, m_container.vertices[0].position.y);
	auto boundaries = m_containerBody->getBoundaries();
	for (auto pos : boundaries)
	{
		printf(" Pixel Pos : (%f, %f)", pos.x, pos.y);
	}*/
}

void World::update(float deltaTime)
{	
	m_physics->update(deltaTime * m_timeScale, m_numericalApproximationMethod);
	m_gas->setMoleculeBodyList(m_physics->getMoleculeBodyList());
	m_gas->update(deltaTime * m_timeScale);
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
		ImGui::SliderFloat("Time Scale", &m_timeScale, -10.0f, 10.0f);
		
		// Combo Box
		const char* items[] = { "Forward Time-Driven", "Backward Time-Driven", "Event-Driven" };
		static int item_current = 1;
		ImGui::ListBox("Simulation Method", &item_current, items, IM_ARRAYSIZE(items));
		m_numericalApproximationMethod = items[item_current];
	}
	m_gas->renderGui();
	if (ImGui::Button("Reload Gas"))
	{
		reload();
	}
}

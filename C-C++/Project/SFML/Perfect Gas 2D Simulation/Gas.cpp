#include "Gas.h"

Gas::Gas(float nMolecules, float volume, float temperature) 
	: m_nMolecules(nMolecules), m_volume(volume), m_temperature(temperature)
{
	long double boltzmann_constant = 1.380649e-23l; // joule per kelvin
	m_pressure = (nMolecules * boltzmann_constant * temperature) / volume; // pascal

	m_xPosMax = (float)WIN_WIDTH;
	m_yPosMax = (float)WIN_HEIGHT;

	m_gasParams = { &m_nMolecules, &m_volume, &m_temperature,
									&m_xPosMin, &m_xPosMax, &m_yPosMin, &m_yPosMax,
									&m_xVelMin, &m_xVelMax, &m_yVelMin, &m_yVelMax,
									&m_moleculeSizePercentage };
	m_cpyGasParams = { m_nMolecules, m_volume, m_temperature,
									m_xPosMin, m_xPosMax, m_yPosMin, m_yPosMax,
									m_xVelMin, m_xVelMax, m_yVelMin, m_yVelMax, 
									m_moleculeSizePercentage };
}

void Gas::create()
{
	m_moleculeRadius = sqrt((m_moleculeSizePercentage * WIN_WIDTH * WIN_HEIGHT) / (M_PI * m_nMolecules));
	std::random_device gen;
	for (int i = 0; i < m_nMolecules; i++)
	{
		// Random Generator
		std::uniform_real_distribution<float> xPosRNG(m_xPosMin + m_moleculeRadius * 2, m_xPosMax - m_moleculeRadius * 2);
		std::uniform_real_distribution<float> yPosRNG(m_yPosMin + m_moleculeRadius * 2, m_yPosMax - m_moleculeRadius * 2);
		std::uniform_real_distribution<float> xVelRNG(m_xVelMin, m_xVelMax);
		std::uniform_real_distribution<float> yVelRNG(m_yVelMin, m_yVelMax);

		// Shape, RenderTexture, Texture
		m_molecule = new Molecule;
		m_molecule->shape.setPosition({ 0, 0 });
		m_molecule->shape.setRadius(m_moleculeRadius);
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

		// Initial Acceleration
		m_molecule->acceleration = sf::Vector2f(0.0f, 0.0f);

		m_moleculeList.push_back(m_molecule);
		
		// Création du corps physique de la molécule
		m_moleculeBody = new Body();
		m_moleculeShape = new Shape();
		m_moleculeShape->setType(Shape::Type::Circle);
		m_moleculeBody->setShape(m_moleculeShape);
		m_moleculeBody->setPosition(m_molecule->position);
		m_moleculeBody->setVelocity(m_molecule->velocity);
		m_moleculeBody->setAcceleration(m_molecule->acceleration);
		m_moleculeBody->setSize(m_molecule->size);
		m_moleculeBodyList.push_back(m_moleculeBody);
		/*
		printf("Molecule Position : (%f, %f)\n", m_moleculeBody->getPosition().x, m_moleculeBody->getPosition().y);
		auto boundaries = m_moleculeBody->getBoundaries();
		for (auto pos : boundaries)
		{
			printf(" Pixel Pos: (%f, %f)", pos.x, pos.y); // positions de chaque pixels qui composent les contours de la molécule
		}*/
	}
}

void Gas::destroy()
{
	for (int i = 0; i < m_moleculeList.size() && i < m_moleculeBodyList.size(); i++)
	{
		delete m_moleculeList[i];
		delete m_moleculeBodyList[i];
	}
	delete m_moleculeShape;
	m_moleculeList.clear();
	m_moleculeBodyList.clear();
}

void Gas::renderGui()
{
	if (ImGui::CollapsingHeader("Gas Settings"))
	{
		ImGui::SliderFloat("Number of Molecules", &m_cpyGasParams[0], 1.0f, 10000.0f);
		ImGui::SliderFloat("Volume", &m_cpyGasParams[1], 0.01f, 10.0f);
		ImGui::SliderFloat("Temperature", &m_cpyGasParams[2], -273.0f, 1000.0f);
		ImGui::SliderFloat("Minimal Position on X axis", &m_cpyGasParams[3], 0.0f, WIN_WIDTH);
		ImGui::SliderFloat("Maximal Position on X axis", &m_cpyGasParams[4], 0.0f, WIN_WIDTH);
		ImGui::SliderFloat("Minimal Position on Y axis", &m_cpyGasParams[5], 0.0f, WIN_HEIGHT);
		ImGui::SliderFloat("Maximal Position on Y axis", &m_cpyGasParams[6], 0.0f, WIN_HEIGHT);
		ImGui::SliderFloat("Minimal Velocity on X axis", &m_cpyGasParams[7], -1000.0f, 1000.0f);
		ImGui::SliderFloat("Maximal Velocity on X axis", &m_cpyGasParams[8], -1000.0f, 1000.0f);
		ImGui::SliderFloat("Minimal Velocity on Y axis", &m_cpyGasParams[9], -1000.0f, 1000.0f);
		ImGui::SliderFloat("Maximal Velocity on Y axis", &m_cpyGasParams[10], -1000.0f, 1000.0f);
		ImGui::SliderFloat("Percentage of surface area occupied by the molecules", &m_cpyGasParams[11], 0.0f, 1.0f);
	}
}

void Gas::update(float deltaTime)
{ 
	for (int i = 0; i < m_moleculeList.size() && i < m_moleculeBodyList.size(); i++)
	{
		m_moleculeList[i]->position = m_moleculeBodyList[i]->getPosition();
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

void Gas::setNewInitialCondition()
{
	for (int i = 0; i < m_cpyGasParams.size() && i < m_cpyGasParams.size(); i++)
	{
		*m_gasParams[i] = m_cpyGasParams[i];
	}
}

void Gas::setm_moleculeRadius(float radius)
{
	m_moleculeRadius = radius;
}

const float Gas::getMoleculeRadius() const
{
	return m_moleculeRadius;
}

void Gas::setMoleculeBodyList(std::vector<Body*> bodies)
{
	m_moleculeBodyList = bodies;
}

const std::vector<Body*> Gas::getMoleculeBodyList() const
{
	return m_moleculeBodyList;
}

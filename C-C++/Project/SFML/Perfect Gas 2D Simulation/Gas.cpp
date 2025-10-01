#include "Gas.h"

long double boltzmann_constant = 1.380649e-23l; // joule per kelvin

Gas::Gas(float nMolecules, float volume, float temperature) 
	: m_nMolecules(nMolecules), m_volume(volume), m_temperature(temperature)
{
	m_xPosMax = (float)WIN_WIDTH;
	m_yPosMax = (float)WIN_HEIGHT;

	m_pressure = (nMolecules * boltzmann_constant * temperature) / volume; // pascal
	m_pressure *= m_pressureScaling;

	m_gasParams = { &m_nMolecules, &m_pressure, &m_volume, &m_temperature,
									&m_xPosMin, &m_xPosMax, &m_yPosMin, &m_yPosMax,
									&m_xVelMin, &m_xVelMax, &m_yVelMin, &m_yVelMax,
									&m_moleculeSizePercentage };
	m_cpyGasParams = { m_nMolecules, m_pressure, m_volume, m_temperature,
									m_xPosMin, m_xPosMax, m_yPosMin, m_yPosMax,
									m_xVelMin, m_xVelMax, m_yVelMin, m_yVelMax, 
									m_moleculeSizePercentage };
}

Gas::~Gas()
{
	for (int i = 0; i < m_moleculeList.size(); i++)
	{
		delete m_moleculeList[i];
		delete m_moleculeBodyList[i];
		delete m_moleculeShapeList[i];
	}
}

void Gas::computeGasParameters()
{
	float* N = &m_cpyGasParams[0]; // sans unité
	float* P = &m_cpyGasParams[1]; // Pascal, multiplié par 1e20
	float* V = &m_cpyGasParams[2]; // Litre
	float* T = &m_cpyGasParams[3]; // Kelvin

	if (*P != *m_gasParams[1]) // Pression
		*P /= m_pressureScaling; // remise à l'échelle réel pour que les valeurs des autres quantité soient cohérentes

	std::vector<int> unchangedParamsIdx{};

	for (int i = 0; i < 4; i++) // N, P, V, T
	{
		if (m_cpyGasParams[i] == *m_gasParams[i])
			unchangedParamsIdx.push_back(i);
	}
	if (unchangedParamsIdx.empty())
		// Tous les paramètres ont changé, je choisis arbitrairement que N soit celui qui soit recalculé
		unchangedParamsIdx.push_back(0); // ajoute N : nombre de molécule

	if (unchangedParamsIdx.size() == 4)
		return;

	int idx = unchangedParamsIdx[0]; // un seul paramètres à recalculer

	if (idx == 0)
		*N = (*V * *P) / (boltzmann_constant * *T);
	else if (idx == 1)
		*P = (*N * boltzmann_constant * *T) / *V;
	else if (idx == 2)
		*V = (*N * boltzmann_constant * *T) / *P;
	else if (idx == 3)
		*T = (*V * *P) / (boltzmann_constant * *N);
	*P *= m_pressureScaling; // Constante pour avoir une valeur affichable, car le nombre de molécule est trop faible
}

void Gas::create()
{
	computeGasParameters();
	setNewInitialCondition();

	m_moleculeRadius = sqrt((m_moleculeSizePercentage * WIN_WIDTH * WIN_HEIGHT) / (M_PI * m_nMolecules));
	m_moleculeRadius = (m_moleculeRadius < 1) ? 1 : m_moleculeRadius;
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
		
		// Création du corps physique de la molécule
		m_moleculeBody = new Body();
		m_moleculeShape = new Shape();
		m_moleculeShape->setType(Shape::Type::Circle);
		m_moleculeBody->setShape(m_moleculeShape);
		m_moleculeBody->setPosition(m_molecule->position);
		m_moleculeBody->setVelocity(m_molecule->velocity);
		m_moleculeBody->setAcceleration(m_molecule->acceleration);
		m_moleculeBody->setSize(m_molecule->size);

		// Ajout des composants des molécules dans des vecteurs
		m_moleculeList.push_back(m_molecule);
		m_moleculeShapeList.push_back(m_moleculeShape);
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
		ImGui::SliderFloat("Number of Molecules", &m_cpyGasParams[0], 0.0f, 1e4f);
		ImGui::SliderFloat("Pressure", &m_cpyGasParams[1], 0.0f, 1e3f);
		ImGui::SliderFloat("Volume", &m_cpyGasParams[2], 0.000001f, 10.f);
		ImGui::SliderFloat("Temperature", &m_cpyGasParams[3], -273.0f, 1e3f);
		ImGui::SliderFloat("Minimal Position on X axis", &m_cpyGasParams[4], 0.0f, WIN_WIDTH);
		ImGui::SliderFloat("Maximal Position on X axis", &m_cpyGasParams[5], 0.0f, WIN_WIDTH);
		ImGui::SliderFloat("Minimal Position on Y axis", &m_cpyGasParams[6], 0.0f, WIN_HEIGHT);
		ImGui::SliderFloat("Maximal Position on Y axis", &m_cpyGasParams[7], 0.0f, WIN_HEIGHT);
		ImGui::SliderFloat("Minimal Velocity on X axis", &m_cpyGasParams[8], -1000.0f, 1000.0f);
		ImGui::SliderFloat("Maximal Velocity on X axis", &m_cpyGasParams[9], -1000.0f, 1000.0f);
		ImGui::SliderFloat("Minimal Velocity on Y axis", &m_cpyGasParams[10], -1000.0f, 1000.0f);
		ImGui::SliderFloat("Maximal Velocity on Y axis", &m_cpyGasParams[11], -1000.0f, 1000.0f);
		ImGui::SliderFloat("Percentage of surface area occupied by the molecules", &m_cpyGasParams[12], 0.0f, 1.0f);
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
		renderer.draw(molecule->texture, molecule->position, molecule->size, molecule->size / 2.f); // origine au centre
		//printf("Molecule position : (%f, %f)\n", molecule->position.x, molecule->position.y);
	}
}

void Gas::setNewInitialCondition()
{
	for (int i = 0; i < m_cpyGasParams.size(); i++)
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

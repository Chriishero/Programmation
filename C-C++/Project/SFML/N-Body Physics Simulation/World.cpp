#include "World.h"
#include <random>

float G = 6.67430e-11f; // constante gravitationnelle 

World::World(int nBody, float timeScale, std::string approximationMethod) : 
	m_nBody(nBody), m_timeScale(timeScale), m_approximationMethod(approximationMethod)
{
}

void World::create()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> distDistrib(m_distMin, m_distMax);
	std::uniform_real_distribution<float> angleDistrib(m_angleMin, m_angleMax);
	std::uniform_real_distribution<float> massDistrib(m_massMin, m_massMax);

	m_vecBody.clear();

	m_body = new Body(m_centralRadius, sf::Vector2f(600, 460), sf::Vector2f(0, 0), m_centralMass);
	m_body->begin();
	m_vecBody.push_back(m_body);

	for (int i = 1; i < m_nBody; i++) {
		float dist = distDistrib(gen);
		float theta = angleDistrib(gen);
		float mass = massDistrib(gen);

		sf::Vector2f position(dist * cos(theta), dist * sin(theta));

		float speed = sqrt(G * m_centralMass / (dist)); // vitesse pour approximer une orbite circulaire
		sf::Vector2f velocity(-speed * sin(theta), speed * cos(theta));
		velocity /= m_pixelToMeter;
		//std::cout << velocity.x << " " << velocity.y << std::endl;

		m_body = new Body(1.0f, position + sf::Vector2f(600, 460), velocity, mass);
		m_body->begin();
		m_vecBody.push_back(m_body);
	}
}

void World::setGui(tgui::GuiSFML& gui)
{
	std::vector<std::shared_ptr<tgui::Slider>> sliderVec{};
	varVec = {m_distMin, m_distMax, m_angleMin, m_angleMax, log10(m_massMin), log10(m_massMax), m_centralRadius, log10(m_centralMass), log10(m_pixelToMeter), (float)m_nBody};
	std::vector<std::string> nameVarVec{"distMin", "distMax", "angleMin", "angleMax", "massMin",
		"massMax", "centralRadius", "centralMass", "physicalScale", "nBody"};
	
	std::vector<float> maxValues = { 2000.0f, 2000.0f, 2 * M_PI, 2 * M_PI, 32, 32, 1000.0f, 37, 20, 3e3};

	for (int i = 0; i < (varVec.size()+1) / 2; i++) {
		for (int j = 0; j < 2; j++) {
			int index = i * 2 + j;
			if (index >= varVec.size()) break;

			auto slider = tgui::Slider::create(0, maxValues[index]);
			slider->setValue(varVec[index]);
			slider->setPosition({ 5 + 165 * j, 0 + 50 * i });
			slider->setSize({ 150, 20 });
			gui.add(slider);

			auto label = tgui::Label::create(nameVarVec[index] + ": " + std::to_string(varVec[index]));
			label->setPosition({ 5 + 165 * j, 0 + 50 * i + 25 });
			gui.add(label);

			slider->onValueChange([label, this, nameVarVec, index](float value) {
				label->setText(nameVarVec[index] + ": " + std::to_string(value));
				varVec[index] = value;
				});
		}
	}
	auto button = tgui::Button::create("Update");
	button->setPosition({ 0, 25 * (varVec.size() + 1) });
	button->setSize({ 200, 40 });
	gui.add(button);
	button->onPress([=]() {
		for (int i = 0; i < varVec.size(); i++) {
			m_distMin = varVec[0];
			m_distMax = varVec[1];
			m_angleMin = varVec[2];
			m_angleMax = varVec[3];
			m_massMin = pow(10, varVec[4]);
			m_massMax = pow(10, varVec[5]);
			m_centralRadius = varVec[6];
			m_centralMass = pow(10, varVec[7]);
			m_pixelToMeter = pow(10, varVec[8]);
			m_nBody = varVec[9];
			World::create();
		}
		});

	auto slider = tgui::Slider::create(0.01f, 3600.f);
	slider->setValue(m_timeScale);
	slider->setPosition({1200 - 160, 0});
	slider->setSize({ 150, 20 });
	gui.add(slider);

	auto label = tgui::Label::create("Time Scale : " + std::to_string(m_timeScale));
	label->setPosition({ 1200 - 160, 20 });
	gui.add(label);

	slider->onValueChange([label, this](float value) {
		label->setText("Time Scale : " + std::to_string(value));
		m_timeScale = value;
		});

	label = tgui::Label::create("Numerical Approximation Method : ");
	label->setPosition({ 1200 - 410, 0 });
	gui.add(label);
	auto comboBox = tgui::ComboBox::create();
	comboBox->setPosition({ 1200 - 410}, 25);
	comboBox->setSize({ 200, 20 });
	comboBox->addItem("Explicit Euler");
	comboBox->addItem("Implicit Euler");
	comboBox->addItem("Verlet");
	comboBox->addItem("Runge-Kutta 2nd-Order");
	comboBox->addItem("Runge-Kutta 4th-Order");
	comboBox->setSelectedItem(m_approximationMethod);
	gui.add(comboBox);

	comboBox->onItemSelect([this](const tgui::String& item) {
		m_approximationMethod = item.toStdString();
	});
}

sf::Vector2f World::newtonRaphsonMethod(sf::Vector2f acceleration, sf::Vector2f velocity, sf::Vector2f position)
{
	
	return acceleration;
}

std::vector<sf::Vector2f> World::computeAcceleration(std::vector<sf::Vector2f> velocities, std::vector<sf::Vector2f> positions)
{
	std::vector<sf::Vector2f> accelerations(m_nBody, sf::Vector2f(0.0f, 0.0f));
	double softening = 0.1f * m_pixelToMeter; // adoucissement pour éviter les singularités
	for (int i = 0; i < m_vecBody.size(); i++) {
		sf::Vector2f position_i = positions.empty() ? m_vecBody[i]->getm_position() : positions[i];
		sf::Vector2f velocity_i = velocities.empty() ? m_vecBody[i]->getm_velocity() : velocities[i];
		for (int j = i + 1; j < m_vecBody.size(); j++) {
			sf::Vector2f position_j = positions.empty() ? m_vecBody[j]->getm_position() : positions[j];

			sf::Vector2f delta = (position_j - position_i) * m_pixelToMeter;
			//std::cout << "delta : " << delta.x << " " << delta.y << std::endl;
			float rij = sqrt(delta.x * delta.x + delta.y * delta.y) + softening;
			//std::cout << "rij : " << rij << std::endl;

			accelerations[i] += G * m_vecBody[j]->getm_weight() * delta / (rij * rij * rij);
			accelerations[j] -= G * m_vecBody[i]->getm_weight() * delta / (rij * rij * rij);
			//std::cout << "acceleration[" << i << "] : " << accelerations[i].x << " " << accelerations[i].y << std::endl;
		}
	}
	return accelerations;
}

void World::motion(float deltaTime) {
	if (m_approximationMethod == "Explicit Euler") {
		std::vector<sf::Vector2f> accelerations = computeAcceleration();
		for (int i = 0; i < m_nBody; i++) {
			m_vecBody[i]->setm_acceleration(accelerations[i]);
			m_vecBody[i]->update(deltaTime);
		}
	}
	else if (m_approximationMethod == "Implicit Euler") {
		std::vector<sf::Vector2f> accelerations {};
		for (int i = 0; i < m_nBody; i++) {
			accelerations[i] = newtonRaphsonMethod(m_vecBody[i]->getm_acceleration(), m_vecBody[i]->getm_velocity(), 
				m_vecBody[i]->getm_position());
			m_vecBody[i]->setm_acceleration(accelerations[i]);
			m_vecBody[i]->update(deltaTime);
		}
	}
	else if (m_approximationMethod == "Verlet") {
		std::vector<sf::Vector2f> accelerations = computeAcceleration();
		for (int i = 0; i < m_nBody; i++) {
			m_vecBody[i]->setm_acceleration(accelerations[i]);
			m_vecBody[i]->setm_position(m_vecBody[i]->getm_position() + deltaTime * m_vecBody[i]->getm_velocity()
				+ deltaTime * deltaTime / 2.0f * accelerations[i]);
		}
		accelerations = computeAcceleration();
		for (int i = 0; i < m_nBody; i++) {
			m_vecBody[i]->setm_velocity(m_vecBody[i]->getm_velocity() + deltaTime / 2.0f
				* (m_vecBody[i]->getm_acceleration() + accelerations[i]));
		}
	}
	else if(m_approximationMethod == "Runge-Kutta 2nd-Order")
	{
		std::vector<sf::Vector2f> k1_acceleration, k1_velocity(m_nBody), k1_position(m_nBody);
		std::vector<sf::Vector2f> k2_acceleration, k2_velocity(m_nBody), k2_position(m_nBody);

		for (int i = 0; i < m_nBody; i++) {
			k1_velocity[i] = m_vecBody[i]->getm_velocity();
			k1_position[i] = m_vecBody[i]->getm_position();
		}
		k1_acceleration = computeAcceleration(k1_velocity, k1_position);

		for (int i = 0; i < m_nBody; i++) {
			k2_velocity[i] = k1_velocity[i] + k1_acceleration[i] * deltaTime / 2.0f;
			k2_position[i] = k1_position[i] + k1_velocity[i] * deltaTime / 2.0f;
		}
		k2_acceleration = computeAcceleration(k2_velocity, k2_position);

		for (int i = 0; i < m_nBody; i++) {
			m_vecBody[i]->setm_acceleration(k2_acceleration[i]);
			m_vecBody[i]->setm_velocity(k1_velocity[i] + deltaTime * k2_acceleration[i]);
			m_vecBody[i]->setm_position(k1_position[i] + deltaTime * k2_velocity[i]);
		}
	}
	else if (m_approximationMethod == "Runge-Kutta 4th-Order")
	{
		std::vector<sf::Vector2f> k1_acceleration, k1_velocity(m_nBody), k1_position(m_nBody);
		std::vector<sf::Vector2f> k2_acceleration, k2_velocity(m_nBody), k2_position(m_nBody);
		std::vector<sf::Vector2f> k3_acceleration, k3_velocity(m_nBody), k3_position(m_nBody);
		std::vector<sf::Vector2f> k4_acceleration, k4_velocity(m_nBody), k4_position(m_nBody);
		
		for (int i = 0; i < m_nBody; i++) {
			k1_velocity[i] = m_vecBody[i]->getm_velocity();
			k1_position[i] = m_vecBody[i]->getm_position();
		}
		k1_acceleration = computeAcceleration(k1_velocity, k1_position);
		for (int i = 0; i < m_nBody; i++) {
			k2_velocity[i] = k1_velocity[i] + k1_acceleration[i] * deltaTime / 2.0f;
			k2_position[i] = k1_position[i] + k1_velocity[i] * deltaTime / 2.0f;
		}
		k2_acceleration = computeAcceleration(k2_velocity, k2_position);
		for (int i = 0; i < m_nBody; i++) {
			k3_velocity[i] = k2_velocity[i] + k2_acceleration[i] * deltaTime / 2.0f;
			k3_position[i] = k2_position[i] + k2_velocity[i] * deltaTime / 2.0f;
		}
		k3_acceleration = computeAcceleration(k3_velocity, k3_position);
		for (int i = 0; i < m_nBody; i++) {
			k4_velocity[i] = k3_velocity[i] + k3_acceleration[i] * deltaTime;
			k4_position[i] = k3_position[i] + k3_velocity[i] * deltaTime;
		}
		k4_acceleration = computeAcceleration(k4_velocity, k4_position);

		for (int i = 0; i < m_nBody; i++) {
			m_vecBody[i]->setm_acceleration(k4_acceleration[i]);
			m_vecBody[i]->setm_velocity(k1_velocity[i] + deltaTime / 6.0f *
				(k1_acceleration[i] + 2.0f * k2_acceleration[i] + 2.0f * k3_acceleration[i] + k4_acceleration[i]));
			m_vecBody[i]->setm_position(k1_position[i] + deltaTime / 6.0f *
				(k1_velocity[i] + 2.0f * k2_velocity[i] + 2.0f * k3_velocity[i] + k4_velocity[i]));
		}
	}
}

void World::update(float deltaTime)
{
	float dt = deltaTime * m_timeScale;
	motion(dt);
}

void World::render(Renderer& renderer)
{
	for (int i = 0; i < m_nBody; i++) {
		m_vecBody[i]->render(renderer);
	}
}

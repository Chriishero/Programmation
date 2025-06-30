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
	comboBox->addItem("Euler");
	comboBox->addItem("Runge-Kutta 2nd-Order");
	comboBox->addItem("Runge-Kutta 4nd-Order");
	comboBox->setSelectedItem(m_approximationMethod);
	gui.add(comboBox);

	comboBox->onItemSelect([this](const tgui::String& item) {
		m_approximationMethod = item.toStdString();
	});
}

std::vector<sf::Vector2f> World::computeAcceleration()
{
	std::vector<sf::Vector2f> accelerations(m_nBody, sf::Vector2f(0.0f, 0.0f));
	double softening = 0.1f * m_pixelToMeter; // adoucissement pour éviter les singularités
	for (int i = 0; i < m_vecBody.size(); i++) {
		for (int j = i + 1; j < m_vecBody.size(); j++) {
			sf::Vector2f delta = (m_vecBody[j]->getm_position() - m_vecBody[i]->getm_position()) * m_pixelToMeter;
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
	if (m_approximationMethod == "Euler") {
		std::vector<sf::Vector2f> accelerations = computeAcceleration();
		for (int i = 0; i < m_nBody; i++) {
			m_vecBody[i]->setm_acceleration(accelerations[i]);
			m_vecBody[i]->update(deltaTime);
		}
	}
	else if(m_approximationMethod == "Runge-Kutta 2nd-Order")
	{
		for (int iter = 0; iter < 2; iter++) {
			std::vector<sf::Vector2f> accelerations = computeAcceleration();
			for (int i = 0; i < m_nBody; i++) {
				m_vecBody[i]->setm_acceleration(accelerations[i]);
				m_vecBody[i]->update(deltaTime / 2.0f);
			}
		}
	}
	else if (m_approximationMethod == "Runge-Kutta 4nd-Order")
	{
		std::vector<sf::Vector2f> accelerations = computeAcceleration();
		std::vector<sf::Vector2f> k1_velocity(m_nBody), k1_position(m_nBody);
		std::vector<sf::Vector2f> k2_velocity(m_nBody), k2_position(m_nBody);
		std::vector<sf::Vector2f> k3_velocity(m_nBody), k3_position(m_nBody);
		
	}
}

void World::update(float deltaTime)
{
	float dt = deltaTime * m_timeScale;
	motion(dt);
	for (int i = 0; i < m_nBody; i++) {
		//if(m_approximationMethod == "Euler") m_vecBody[i]->update(dt);
		//if(m_approximationMethod == "Runge-Kutta 2nd-Order") m_vecBody[i]->update(dt / 2.0f);
	}
}

void World::render(Renderer& renderer)
{
	for (int i = 0; i < m_nBody; i++) {
		m_vecBody[i]->render(renderer);
	}
}

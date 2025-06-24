#include "World.h"
#include <random>

float G = 6.67430e-11f; // constante gravitationnelle 

World::World(int nBody) : m_nBody(nBody)
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

		float speed = sqrt(G * m_centralMass / (dist * m_pixelToMeter)) / m_pixelToMeter; // vitesse pour approximer une orbite circulaire
		sf::Vector2f velocity(-speed * sin(theta), speed * cos(theta));

		m_body = new Body(1.0f, position + sf::Vector2f(600, 460), velocity, mass);
		m_body->begin();
		m_vecBody.push_back(m_body);
	}
}

void World::setGui(tgui::GuiSFML& gui)
{
	std::vector<std::shared_ptr<tgui::Slider>> sliderVec{};
	varVec = {m_distMin, m_distMax, m_angleMin, m_angleMax, log(m_massMin), log(m_massMax), m_centralRadius, log(m_centralMass)};
	std::vector<std::string> nameVarVec{"distMin", "distMax", "angleMin", "angleMax", "massMin",
		"massMax", "centralRadius", "centralMass"};
	
	std::vector<float> maxValues = { 2000.0f, 2000.0f, 2 * M_PI, 2 * M_PI, 12, 12, 1000.0f, 14};

	for (int i = 0; i < varVec.size() / 2; i++) {
		for (int j = 0; j < 2; j++) {
			int index = i * 2 + j;
			if (index >= varVec.size()) break;

			auto slider = tgui::Slider::create(0, maxValues[index]);
			slider->setValue(varVec[index]);
			slider->setPosition({ 5 + 165 * j, 0 + 50 * i });
			slider->setSize({ 150, 20 });
			gui.add(slider);

			auto label = tgui::Label::create(nameVarVec[index]);
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
			World::create();
		}
		});
}

void World::motion() {
	std::vector<sf::Vector2f> accelerations(m_nBody, sf::Vector2f(0.0f, 0.0f));
	for (int i = 0; i < m_vecBody.size(); i++) {
		for (int j = i + 1; j < m_vecBody.size(); j++) {
			sf::Vector2f delta = (m_vecBody[j]->getm_position() - m_vecBody[i]->getm_position());
			float rij = sqrt(delta.x * delta.x + delta.y * delta.y) + 5.0f;
			sf::Vector2f force = G * m_vecBody[i]->getm_weight() * m_vecBody[j]->getm_weight() * delta / (rij * rij * rij);

			accelerations[i] += force / m_vecBody[i]->getm_weight();
			accelerations[j] -= force / m_vecBody[j]->getm_weight();
		}
	}
	for (int i = 0; i < m_nBody; i++) {
		m_vecBody[i]->setm_acceleration(accelerations[i]);
	}
}

void World::update(float deltaTime)
{
	motion();
	for (int i = 0; i < m_nBody; i++) {
		m_vecBody[i]->update(deltaTime * 1);
	}
}

void World::render(Renderer& renderer)
{
	for (int i = 0; i < m_nBody; i++) {
		m_vecBody[i]->render(renderer);
	}
}

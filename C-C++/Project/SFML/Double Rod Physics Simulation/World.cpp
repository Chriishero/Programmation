#include "World.h"
#include <iostream>
#include <cmath>

World::World(int nRod, float gravity) : m_nRod(nRod), m_gravity(gravity)
{
}

void World::create()
{
	for (int i = 0; i < 2; i++) {
		if(m_vecRod.empty())
			m_rod = new Rode(sf::Vector2f(20, 250), sf::Vector2f(920 / 2, 920 / 2), 30, 0, 1);
		else {
			auto prevPos = m_vecRod[i - 1]->getm_position();
			auto prevSize = m_vecRod[i - 1]->getm_size();
			m_rod = new Rode(prevSize, sf::Vector2f(prevPos.x, prevPos.y + prevSize.y), 30, 0, 1);
		}
		m_vecRod.push_back(m_rod);
	}
}

void World::motion() {
	float theta1 = m_vecRod[0]->getm_angle();
	float theta2 = m_vecRod[1]->getm_angle();
	double dtheta1 = m_vecRod[0]->getm_angularVelocity();
	double dtheta2 = m_vecRod[1]->getm_angularVelocity();
	float m1 = m_vecRod[0]->getm_weight();
	float m2 = m_vecRod[1]->getm_weight();
	float l1 = m_vecRod[0]->getm_size().y;
	float l2 = m_vecRod[1]->getm_size().y;

	float a = (m1 + m2) * l1 * l1;
	float b = m2 * l2 * l2 * cos(theta1 - theta2);
	float c = m2 * l1 * l2 * cos(theta1 - theta2);
	float d = m2 * l2 * l2;
	float f = m2 * dtheta1 * l1 * dtheta2 * l2 * sin(theta1 - theta2) - (m1 + m2) * m_gravity * l1 * sin(theta1) +
		m1 * l1 * l2 * dtheta2 * sin(theta1 - theta2) * (dtheta1 - dtheta2);
	float g = m2 * dtheta1 * l1 * dtheta2 * l2 * sin(theta1 - theta2) - m2 * m_gravity * l2 * sin(theta2) - m2 * l1 * l2 *
		dtheta1 * sin(theta1 - theta2) * (dtheta1 - dtheta2);

	double ddtheta1 = (f * d - g * b) / (a * d - b * c);
	m_vecRod[0]->setm_angularAcceleration(ddtheta1);

	double ddtheta2 = (g * a - f * c) / (a * d - b * c);
	m_vecRod[1]->setm_angularAcceleration(ddtheta2);
}

void World::update(float deltaTime)
{
	m_energy = 0.0f;
	motion();
	for (int i = 0; i < m_vecRod.size(); i++) {
		if (i > 0) {
			auto prevRod = m_vecRod[i - 1];
			sf::Vector2f prevMassPosition(prevRod->getm_massPosition().x - prevRod->getm_massOrigin().x + prevRod->getm_size().x,
										  prevRod->getm_massPosition().y - prevRod->getm_massOrigin().y + prevRod->getm_size().x);
			m_vecRod[i]->setm_jointPosition(prevMassPosition);
			//m_vecRod[i]->setm_angle(m_vecRod[i]->getm_angle() + 5.0f); // pour tester la différence de vitesse entre les 2 pendules
		}
		m_vecRod[i]->update(deltaTime);
		m_energy += m_vecRod[i]->getm_energy();
	}
	//std::cout << "Energy: " << m_energy << std::endl;
}

void World::render(Renderer& renderer)
{
	for (auto rod : m_vecRod) {
		rod->draw(renderer);
	}
}

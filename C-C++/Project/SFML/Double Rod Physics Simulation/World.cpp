#include "World.h"
#include <iostream>
#include <cmath>

World::World(float gravity, float friction) : m_gravity(gravity), m_friction(friction)
{
}

void World::create()
{
	for (int i = 0; i < 2; i++) {
		if(m_vecRod.empty())
			m_rod = new Rode(sf::Vector2f(20, 250), sf::Vector2f(920 / 2, 920 / 2), 90, 2, 1);
		else {
			auto prevPos = m_vecRod[i - 1]->getm_position();
			auto prevSize = m_vecRod[i - 1]->getm_size();
			m_rod = new Rode(prevSize, sf::Vector2f(prevPos.x, prevPos.y + prevSize.y), 270, 0, 1);
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
	float l1 = m_vecRod[0]->getm_size().y / 250.0f; // normalisation des longueurs : 250 pixels = 2.5 m
	float l2 = m_vecRod[1]->getm_size().y / 250.0f; // normalisation des longueurs : 250 pixels = 2.5 m
	float g = m_gravity;

	float kineticEnergy1 = 0.5f  * m1 * dtheta1 * dtheta1 * l1 * l1;
	m_vecRod[0]->setm_kineticEnergy(kineticEnergy1);
	float potentialEnergy1 = -m1 * g * l1 * cos(theta1);
	m_vecRod[0]->setm_potentialEnergy(potentialEnergy1);

	float kineticEnergy2 = 0.5f * m2 * (dtheta1 * dtheta1 * l1 * l1 + 2 * dtheta1 * l1 * dtheta2 * l2 * cos(theta1 - theta2)
							+ dtheta2 * dtheta2 * l2 * l2);
	m_vecRod[1]->setm_kineticEnergy(kineticEnergy2);
	float potentialEnergy2 = -m2 * g * (l1 * cos(theta1) + l2 * cos(theta2));

	m_energy = kineticEnergy1 + kineticEnergy2 + potentialEnergy1 + potentialEnergy2;

	float a = (m1 + m2) * l1 * l1;
	float b = m2 * l1 * l2 * cos(theta1 - theta2);
	float c = b;
	float d = m2 * l2 * l2;
	float e = - (m1 + m2) * g * l1 * sin(theta1) - m2 * l1 * l2 * dtheta2 * dtheta2 * sin(theta1 - theta2);
	float f = - m2 * g * l2 * sin(theta2) + m2 * l1 * l2 * dtheta1 * dtheta1 * sin(theta1 - theta2);

	double ddtheta1 = (e * d - f * b) / (a * d - b * c);
	ddtheta1 -= m_friction * dtheta1;
	m_vecRod[0]->setm_angularAcceleration(ddtheta1);
	
	double ddtheta2 = (f * a - e * c) / (a * d - b * c);
	ddtheta2 -= m_friction * dtheta2;
	m_vecRod[1]->setm_angularAcceleration(ddtheta2);
}

void World::update(float deltaTime)
{
	motion();
	for (int i = 0; i < m_vecRod.size(); i++) {
		if (i > 0) {
			auto prevRod = m_vecRod[i - 1];
			sf::Vector2f prevMassPosition(prevRod->getm_massPosition().x - prevRod->getm_massOrigin().x + prevRod->getm_size().x,
										  prevRod->getm_massPosition().y - prevRod->getm_massOrigin().y + prevRod->getm_size().x);
			m_vecRod[i]->setm_jointPosition(prevMassPosition);
		}
		m_vecRod[i]->update(deltaTime * m_speedFactor);
	}
	std::cout << "Energy: " << m_energy << std::endl;
}

void World::render(Renderer& renderer)
{
	for (auto rod : m_vecRod) {
		rod->draw(renderer);
	}
}

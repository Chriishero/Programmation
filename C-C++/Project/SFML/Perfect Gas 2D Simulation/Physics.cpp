#include "Physics.h"

Physics::Physics(std::vector<Body*> moleculeBodyList, Body* containerBody) 
	: m_moleculeBodyList(moleculeBodyList), m_containerBody(containerBody)
{}

void Physics::computeNewVelocities(Body* mol1, Body* mol2)
{
	// Vitesses scalaires
	float v1 = sqrt(mol1->getVelocity().x * mol1->getVelocity().x + mol1->getVelocity().y * mol1->getVelocity().y);
	float v2 = sqrt(mol2->getVelocity().x * mol2->getVelocity().x + mol2->getVelocity().y * mol2->getVelocity().y);
	// Angle depuis l'origine
	float theta1 = atan2(mol1->getPosition().y, mol1->getPosition().x);
	float theta2 = atan2(mol2->getPosition().y, mol2->getPosition().x);
	// Angle de contact des deux molécules
	float posX = mol1->getPosition().x - mol2->getPosition().x;
	float posY = mol1->getPosition().y - mol2->getPosition().y;
	float phi = atan2(posY, posX);
	float m1 = 1;
	float m2 = 1;

	// Nouvelle vitesse de la molécule 1
	float v1X_prime = (v1 * cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * cos(theta2 - phi)) / (m1 + m2) 
				* (cos(phi) + v1 * sin(theta1 - phi) * cos(phi + M_PI / 2));
	float v1Y_prime = (v1 * cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * cos(theta2 - phi)) / (m1 + m2)
		* (sin(phi) + v1 * sin(theta1 - phi) * sin(phi + M_PI / 2));
	mol1->setVelocity({ v1X_prime, v1Y_prime });

	// Nouvelle vitesse de la molécule 2
	float v2X_prime = (v2 * cos(theta2 - phi) * (m2 - m1) + 2 * m1 * v1 * cos(theta1 - phi)) / (m2 + m1)
		* (cos(phi) + v2 * sin(theta2 - phi) * cos(phi + M_PI / 2));
	float v2Y_prime = (v2 * cos(theta1 - phi) * (m2 - m1) + 2 * m1 * v1 * cos(theta1 - phi)) / (m2 + m1)
		* (sin(phi) + v2 * sin(theta1 - phi) * sin(phi + M_PI / 2));
	printf("v2_prime : (%f, %f)", v2X_prime, v2Y_prime);
	mol2->setVelocity({ v2X_prime, v2Y_prime });
}

void Physics::checkMapCollisions()
{
	//printf("%d", m_containerBody->getPosition().x + m_containerBody->getSize().x);
	for (int i = 0; i < m_moleculeBodyList.size(); i++)
	{
		Body* m = m_moleculeBodyList[i];
		if (m->getPosition().x <= m_containerBody->getPosition().x
			|| m->getPosition().x + m->getSize().x * 2 >= m_containerBody->getPosition().x + m_containerBody->getSize().x
			|| m->getPosition().y <= m_containerBody->getPosition().y
			|| m->getPosition().y + m->getSize().y * 2 >= m_containerBody->getPosition().y + m_containerBody->getSize().y)
		{
			m->setVelocity(-m->getVelocity());
		}
	}
}

void Physics::checkMoleculesCollisions()
{/*
	for (int i = 0; i < m_moleculeBodyList.size(); i++)
	{
		std::vector<sf::Vector2f> boundaries1 = m_moleculeBodyList[i]->getBoundaries();
		for (int j = i + 1; j < m_moleculeBodyList.size(); j++)
		{
			std::vector<sf::Vector2f> boundaries2 = m_moleculeBodyList[j]->getBoundaries();
			for (auto b1 : boundaries1)
			{
				for (auto b2 : boundaries2)
				{
					if ((sf::Vector2i)b1 == (sf::Vector2i)b2)
					{
						printf("Collisions entre molécule %d et molécule %d.\n", i, j);
						m_moleculeBodyList[i]->setVelocity({ 0, 0 });
						m_moleculeBodyList[j]->setVelocity({ 0, 0 });
						return ; // arrêter les deux boucles dès qu'il y a une collision, pour passer à la prochaine molécule
					}
				}
			}
		}
	}*/
	for (int i = 0; i < m_moleculeBodyList.size(); i++)
	{
		Body* m1 = m_moleculeBodyList[i];
		float radius1 = m1->getSize().x;
		for (int j = i + 1; j < m_moleculeBodyList.size(); j++)
		{
			Body* m2 = m_moleculeBodyList[j];
			float radius2 = m2->getSize().y;
			float distance = sqrt(pow((m2->getPosition().x - m1->getPosition().x), 2) + pow((m2->getPosition().y - m1->getPosition().y), 2));
			if ((distance > 0 && distance < radius1 + radius2) || (distance < 0 && -distance < radius1 + radius2))
			{
				printf("Collisions entre molécule %d et molécule %d.\n", i, j);
				computeNewVelocities(m1, m2);
				sf::Vector2f v1 = m1->getVelocity();
				sf::Vector2f v2 = m2->getVelocity();
				//m_moleculeBodyList[i]->setVelocity(v2);
				//m_moleculeBodyList[j]->setVelocity(v1);
			}
		}
	}
}

void Physics::update(float deltaTime, std::string method)
{
	checkMapCollisions();
	checkMoleculesCollisions();
	for (auto &molecule : m_moleculeBodyList)
	{
		molecule->setVelocity(molecule->getVelocity() + molecule->getAcceleration() * deltaTime);
		molecule->setPosition(molecule->getPosition() + molecule->getVelocity() * deltaTime);
	}
}

void Physics::setMoleculeBodyList(std::vector<Body*> moleculeBodyList)
{
	m_moleculeBodyList = moleculeBodyList;
}

const std::vector<Body*> Physics::getMoleculeBodyList() const
{
	return m_moleculeBodyList;
}

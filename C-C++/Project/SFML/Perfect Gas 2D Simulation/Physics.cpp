#include "Physics.h"

Physics::Physics(std::vector<Body*> moleculeBodyList, Body* containerBody) 
	: m_moleculeBodyList(moleculeBodyList), m_containerBody(containerBody)
{}

void Physics::computeNewVelocities(Body* mol1, Body* mol2)
{
	// Positions
	float x1 = mol1->getPosition().x;
	float y1 = mol1->getPosition().y;
	float x2 = mol2->getPosition().x;
	float y2 = mol2->getPosition().y;
	// Vitesses vectorielles initiales
	sf::Vector2f v1_i = mol1->getVelocity();
	sf::Vector2f v2_i = mol2->getVelocity();
	// Masses
	float m1 = 1;
	float m2 = 1;
	// Angle molécule 1
	float alpha1 = atan2(y2 - y1, x2 - x1);
	float beta1 = atan2(v1_i.y, v1_i.x);
	float gamma1 = beta1 - alpha1;
	// Angles molécule 2
	float alpha2 = atan2(y1 - y2, x1 - x2);
	float beta2 = atan2(v2_i.y, v2_i.x);
	float gamma2 = beta2 - alpha2;
	// Normes des vitesses initiales
	float v12_i = sqrt(v1_i.x * v1_i.x + v1_i.y * v1_i.y) * cos(gamma1); // vitesse transmise au corps 2 par le corps 1
	float v11_i = sqrt(v1_i.x * v1_i.x + v1_i.y * v1_i.y) * sin(gamma1); // vitesse conservé du corps 1
	float v21_i = sqrt(v2_i.x * v2_i.x + v2_i.y * v2_i.y) * cos(gamma2);
	float v22_i = sqrt(v2_i.x * v2_i.x + v2_i.y * v2_i.y) * sin(gamma2);
	// Normes des vitesses finales
	float v12_f = ((m1 - m2) * v12_i - 2 * m2 * v21_i) / (m1 + m2);
	float v21_f = ((m2 - m1) * v21_i - 2 * m1 * v12_i) / (m1 + m2);
	// Vitesses vectorielles finales
	sf::Vector2f v1_f = v11_i * sf::Vector2f{ -sin(alpha1), cos(alpha1) } + v12_f * sf::Vector2f{ cos(alpha1), sin(alpha1) };
	sf::Vector2f v2_f = v22_i * sf::Vector2f{ -sin(alpha2), cos(alpha2) } - v21_f * sf::Vector2f{ cos(alpha2), sin(alpha2) };
	// Application des vitesses finales
	mol1->setVelocity(v1_f);
	mol2->setVelocity(v2_f);
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
			float m1 = 1;
			float m2 = 1;
			float theta = atan2(m->getPosition().y, m->getPosition().x);
			sf::Vector2f v1_prime = m->getVelocity() * sqrt(m1 * m1 + m2 * m2 + 2 * m1 * m2 * cos(theta)) / (m1 + m1);
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

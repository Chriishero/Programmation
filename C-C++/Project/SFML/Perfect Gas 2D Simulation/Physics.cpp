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
	float v21_f = ((m2 - m1) * v21_i + 2 * m1 * v12_i) / (m1 + m2);
	// Vitesses vectorielles finales
	sf::Vector2f v1_f = v11_i * sf::Vector2f{ -sin(alpha1), cos(alpha1) } + v12_f * sf::Vector2f{ cos(alpha1), sin(alpha1) };
	sf::Vector2f v2_f = v22_i * sf::Vector2f{ -sin(alpha2), cos(alpha2) } - v21_f * sf::Vector2f{ cos(alpha2), sin(alpha2) };
	// Application des vitesses finales
	mol1->setVelocity(v1_f);
	mol2->setVelocity(v2_f);
}

int Physics::distanceBetweenMolecules(Body* mol1, Body* mol2)
{
	float radius1 = mol1->getSize().y;
	float radius2 = mol2->getSize().y;
	float distance = sqrt(pow((mol2->getPosition().x - mol1->getPosition().x), 2) + pow((mol2->getPosition().y - mol1->getPosition().y), 2));
	
	return (distance - radius1 - radius2);
}

bool Physics::backtrackToCollision(Body* mol1, Body* mol2)
{
	// Positions vectorielles
	sf::Vector2f q1 = mol1->getPosition();
	sf::Vector2f q2 = mol2->getPosition();
	// Vitesses vectorielles
	sf::Vector2f v1 = mol1->getVelocity();
	sf::Vector2f v2 = mol2->getVelocity();
	// Rayons
	float r1 = mol1->getSize().x;
	float r2 = mol2->getSize().x;

	// Différences des positions vectorielles
	sf::Vector2f dq = { q1.x - q2.x, q1.y - q2.y };
	// Différences des vitesses vectorielles
	sf::Vector2f dv = { v1.x - v2.x, v1.y - v2.y };
	
	// Termes quadratiques
	float a = dv.x * dv.x + dv.y * dv.y;
	float b = 2 * (dq.x * dv.x + dq.y * dv.y);
	float c = dq.x * dq.x + dq.y * dq.y - (r1 + r2) * (r1 + r2);
	// Discriminant
	float disc = b * b - 4 * a * c;

	if (a == 0)
		return false;
	if (disc < 0) // Aucune collision
		return false;

	// Moment exact de la collision (2 solutions)
	float collisionTime = 1.0f;
	float t1 = (-b + sqrt(disc)) / (2 * a);
	float t2 = (-b - sqrt(disc)) / (2 * a);

	if (t1 < 0 && t2 < 0)
		collisionTime = (t1 > t2) ? t1 : t2;
	else
		collisionTime = (t1 < t2) ? t1 : t2;

	if (collisionTime > 0) 
		return false;

	// Application des nouvelles positions
	mol1->setPosition(q1 + v1 * collisionTime);
	mol2->setPosition(q2 + v2 * collisionTime);

	return true;
}

void Physics::updateMapCollisions(std::string method, float deltaTime)
{
	//printf("%d", m_containerBody->getPosition().x + m_containerBody->getSize().x);
	for (int i = 0; i < m_moleculeBodyList.size(); i++)
	{
		Body* m = m_moleculeBodyList[i];
		if (m->getPosition().x <= m_containerBody->getPosition().x
			|| m->getPosition().x + m->getSize().x * 2 >= m_containerBody->getPosition().x + m_containerBody->getSize().x)
		{
			m->setVelocity({ -m->getVelocity().x, m->getVelocity().y });
		}
		else if (m->getPosition().y <= m_containerBody->getPosition().y
			|| m->getPosition().y + m->getSize().y * 2 >= m_containerBody->getPosition().y + m_containerBody->getSize().y)
		{
			m->setVelocity({ m->getVelocity().x, -m->getVelocity().y });
		}
	}
}

void Physics::updateMoleculesCollisions(std::string method, float deltaTime)
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
		Body* mol1 = m_moleculeBodyList[i];
		for (int j = i + 1; j < m_moleculeBodyList.size(); j++)
		{
			Body* mol2 = m_moleculeBodyList[j];
			if (distanceBetweenMolecules(mol1, mol2) <= 0) // true
			{
				if (method == "Backward Time-Driven")
				{
					backtrackToCollision(mol1, mol2);
				}
				printf("Collisions entre molécule %d et molécule %d.\n", i, j);
				computeNewVelocities(mol1, mol2);
			}
		}
	}
}

void Physics::update(float deltaTime, std::string method)
{
	updateMapCollisions(method, deltaTime);
	updateMoleculesCollisions(method, deltaTime);
	for (auto& molecule : m_moleculeBodyList)
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

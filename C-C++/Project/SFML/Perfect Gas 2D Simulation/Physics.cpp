#include "Physics.h"

Physics::Physics(std::vector<Body*> moleculeBodyList) : m_moleculeBodyList(moleculeBodyList)
{}

void Physics::checkMapCollisions()
{
}

void Physics::checkMoleculesCollisions()
{
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
						//m_moleculeBodyList[i]->setVelocity({ 0, 0 });
						//m_moleculeBodyList[j]->setVelocity({ 0, 0 });
						j++;
					}
				}
			}
		}
	}
}

void Physics::update(float deltaTime, std::string method)
{
	checkMoleculesCollisions();
	for (auto &molecule : m_moleculeBodyList)
	{
		molecule->setVelocity(molecule->getVelocity() + molecule->getAcceleration() * deltaTime);
		molecule->setPosition(molecule->getPosition() + molecule->getVelocity() * deltaTime);
	}
}

const std::vector<Body*> Physics::getMoleculeBodyList() const
{
	return m_moleculeBodyList;
}

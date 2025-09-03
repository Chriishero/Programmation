#include "Physics.h"

Physics::Physics(std::vector<Body*> moleculeBodyList) : m_moleculeBodyList(moleculeBodyList)
{}

void Physics::checkMapCollisions()
{
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
						printf("Collisions entre mol�cule %d et mol�cule %d.\n", i, j);
						m_moleculeBodyList[i]->setVelocity({ 0, 0 });
						m_moleculeBodyList[j]->setVelocity({ 0, 0 });
						return ; // arr�ter les deux boucles d�s qu'il y a une collision, pour passer � la prochaine mol�cule
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
				printf("Collisions entre mol�cule %d et mol�cule %d.\n", i, j);
				m_moleculeBodyList[i]->setVelocity({ 0, 0 });
				m_moleculeBodyList[j]->setVelocity({ 0, 0 });
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

void Physics::setMoleculeBodyList(std::vector<Body*> moleculeBodyList)
{
	m_moleculeBodyList = moleculeBodyList;
}

const std::vector<Body*> Physics::getMoleculeBodyList() const
{
	return m_moleculeBodyList;
}

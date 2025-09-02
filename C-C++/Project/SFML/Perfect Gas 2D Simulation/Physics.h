#pragma once

#include "main.hpp"

class Body;

class Physics
{
	public:
		Physics(std::vector<Body*> moleculeBodyList);

		void checkMapCollisions();
		void checkMoleculesCollisions();
		void update(float deltaTime, std::string method); 

		void setMoleculeBodyList(std::vector<Body*> moleculeBodyList);
		const std::vector<Body*> getMoleculeBodyList() const;

	private:
		std::vector<Body*> m_moleculeBodyList;
		std::vector<std::vector<sf::Vector2f>> m_boundariesList;
};


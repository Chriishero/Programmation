#pragma once

#include "main.hpp"

class Body;

class Physics
{
	public:
		Physics(std::vector<Body*> moleculeBodyList, Body* containerBody);

		void computeNewVelocities(Body* mol1, Body* mol2);
		int distanceBetweenMolecules(Body* mol1, Body* mol2);
		bool backtrackToCollision(Body* mol1, Body* mol2);
		bool backtrackToWallCollision(Body* mol);
		void updateMapCollisions(std::string method, float deltaTime);
		void updateMoleculesCollisions(std::string method, float deltaTime);
		void update(float deltaTime, std::string method); 

		void setMoleculeBodyList(std::vector<Body*> moleculeBodyList);
		const std::vector<Body*> getMoleculeBodyList() const;

	private:
		std::vector<Body*> m_moleculeBodyList;
		Body* m_containerBody;
		std::vector<std::vector<sf::Vector2f>> m_boundariesList;
};


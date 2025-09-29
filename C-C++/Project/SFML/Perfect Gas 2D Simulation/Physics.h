#pragma once

#include "main.hpp"

class Body;
class Event;
class EventArray;

class Physics
{
	public:
		Physics(std::vector<Body*> moleculeBodyList, Body* containerBody);
		~Physics();

		void computeNewVelocities(Body* mol1, Body* mol2);
		int distanceBetweenMolecules(Body* mol1, Body* mol2);
		// Backward Time-Driven
		bool backtrackToCollision(Body* mol1, Body* mol2);
		bool backtrackToWallCollision(Body* mol);
		// Event-Driven
		float nextMoleculesCollision(Body* mol1, Body* mol2);
		float nextWallCollision(Body* mol);
		void computeNextEvents();
		// Mise à jour des vitesses après collisions
		void updateMapCollisions(std::string method);
		void updateMoleculesCollisions(std::string method);
		// Update principale
		void update(float deltaTime, std::string method); 

		void setMoleculeBodyList(std::vector<Body*> moleculeBodyList);
		const std::vector<Body*> getMoleculeBodyList() const;

	private:
		std::vector<Body*> m_moleculeBodyList;
		Body* m_containerBody;
		std::vector<std::vector<sf::Vector2f>> m_boundariesList;

		Event* m_event;
		Event* m_nextEvent = nullptr;
		EventArray* eventArray = nullptr;
		
		float m_minEventTime = 0.000001f;
};
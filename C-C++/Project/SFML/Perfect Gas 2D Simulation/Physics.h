#pragma once

#include "main.hpp"

class Physics
{
	public:
		Physics();

		void checkMapCollisions();
		void checkMoleculesCollisions();
		void update(float deltaTime, std::string method); 

	private:
		std::vector<sf::Vector2f>* m_moleculesBoundariesList;
		std::vector<sf::Vector2f> m_containerBoudaries;
};


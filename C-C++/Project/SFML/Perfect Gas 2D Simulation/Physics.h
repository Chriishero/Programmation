#pragma once

#include "main.hpp"


class Physics
{
	public:
		Physics();

		void checkMapCollisions();
		void checkMoleculesCollisions();
		void update(float deltaTime, std::string method);
};


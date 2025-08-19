#pragma once

#include "main.hpp"

class Renderer;
class Gas;

class World
{
	public:
		World();

		void create();
		void update(float deltaTime);
		void render(Renderer& renderer);

	private:
		Gas* m_gas;

		float m_nMolecules;
		float m_volume;
		float m_temperature;
};


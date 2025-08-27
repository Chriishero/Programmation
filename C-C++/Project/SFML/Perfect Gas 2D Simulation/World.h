#pragma once

#include "main.hpp"

class Gas;
class Renderer;

class World
{
	public:
		World();

		void create();
		void createContainer();
		void update(float deltaTime);
		void render(Renderer& renderer);
		void renderGui();

		typedef struct
		{
			sf::VertexArray vertices;
			float outlineThickness;
		} Container;

	private:
		Gas* m_gas;

		// Gas Parameters
		float m_nMolecules;
		float m_volume;
		float m_temperature;

		float m_timeScale = 1.0f;

		Container m_container;
};


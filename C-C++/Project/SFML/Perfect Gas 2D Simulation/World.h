#pragma once

#include "main.hpp"

class Physics;
class Gas;
class Renderer;

class World
{
	public:
		World();
		~World();

		void create();
		void reload();
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
		Physics* m_physics;
		Gas* m_gas;

		// Gas Parameters
		float m_nMolecules;
		float m_volume;
		float m_temperature;

		float m_timeScale = 1.0f;
		std::string m_numericalApproximationMethod = "Backward Time-Driven";

		Container m_container;
		Body* m_containerBody;
		Shape* m_containerShape;
		sf::Vector2f m_containerSize;
};


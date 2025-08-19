#pragma once

#include "main.hpp"

class Renderer;

class Gas
{
	public:
		Gas(float nMolecules, float volume, float temperature);

		void begin();
		void update(float deltaTime);
		void render(Renderer& renderer);

		typedef struct {
			sf::CircleShape shape;
			sf::RenderTexture renderTexture;
			sf::Texture texture;

			sf::Vector2f position;
			sf::Vector2f size;
			sf::Vector2f velocity;
		} Molecule;

	private:
		float m_nMolecules;
		float m_volume;
		float m_temperature;

		float m_pressure = {};

		Molecule* m_molecule;
		std::vector<Molecule*> m_moleculeList{};
};


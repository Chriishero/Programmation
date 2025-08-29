#pragma once

#include "main.hpp"

class Renderer;
class Body;

class Gas // LA STRUCT MOLECULE NE CONTIENT PAS VEL ET ACC, C'EST QUE LE BODY, IDEM POUR LA MISE À JOUR
{
	public:
		Gas(float nMolecules, float volume, float temperature);

		void create();
		void destroy();
		void renderGui();
		void update(float deltaTime);
		void render(Renderer& renderer);

		void setm_moleculeRadius(float radius);

		typedef struct {
			sf::CircleShape shape;
			sf::RenderTexture renderTexture;
			sf::Texture texture;

			sf::Vector2f position;
			sf::Vector2f velocity;
			sf::Vector2f acceleration;
			sf::Vector2f size;
		} Molecule;

	private:
		float m_nMolecules;
		float m_volume;
		float m_temperature;

		float m_pressure = {};

		// Simulation Parameters
		float m_xPosMin = 0.0f;
		float m_xPosMax{};
		float m_yPosMin = 0.0f;
		float m_yPosMax{};

		float m_xVelMin = -500.0f;
		float m_xVelMax = 500.0f;
		float m_yVelMin = -500.0f;
		float m_yVelMax = 500.0f;

		float m_moleculeSizePercentage = 0.05; // pourcentage de l'air total du conteneur occupé par les molécules
		float m_moleculeRadius{};

		std::vector<float*> m_gasParams{};
		std::vector<float> m_cpyGasParams{};

		Molecule* m_molecule;
		std::vector<Molecule*> m_moleculeList{};

		Body* m_moleculeBody;
		std::vector<Body*> m_moleculeBodyList{};
};


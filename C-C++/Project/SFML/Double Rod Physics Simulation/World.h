#pragma once
#include <vector>
#include "Rode.h"
#include "Renderer.h"

class World
{
public:
	World(float gravity, float friction);

	void create();
	void motion();
	void update(float deltaTime);
	void render(Renderer& renderer);

private:
	float m_gravity;
	float m_friction;

	float m_kineticEnergy = 0.0f;
	float m_potentialEnergy = 0.0f;
	float m_energy = 0.0f;
	Rode* m_rod;
	std::vector<Rode*> m_vecRod{};

	float m_speedFactor = 1.0f;
};


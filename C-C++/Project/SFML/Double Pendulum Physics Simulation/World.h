#pragma once
#include <vector>
#include "Rode.h"
#include "Renderer.h"
#include <TGUI/TGUI.hpp>

class World
{
public:
	World(float gravity, float friction);

	void create();
	void setGui(tgui::GuiSFML &gui);
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

	float l1 = 0;
	float l2 = 0;
	float theta1 = 0;
	float theta2 = 0;
	float dtheta1 = 0;
	float dtheta2 = 0;
	float m1 = 0;
	float m2 = 0;
	float frictionTemp = 0.0f;
};


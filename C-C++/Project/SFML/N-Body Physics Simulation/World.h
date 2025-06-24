#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include "Renderer.h"
#include "body.h"

class World
{
public:
	World(int nBody);

	void create();
	void setGui(tgui::GuiSFML &gui);
	void motion();
	void update(float deltaTime);
	void render(Renderer& renderer);

	float M_PI = 3.14159265358979323846f;

private:
	int m_nBody;

	float m_distMin = 0.0f;
	float m_distMax = 1000.0f;
	float m_angleMin = 0.0f;
	float m_angleMax = 2 * M_PI;
	float m_massMin = 1e4f;
	float m_massMax = 1e8f;
	float m_centralRadius = 10.0f;
	float m_centralMass = 1e12f;
	const float m_pixelToMeter = 1e0;

	Body* m_body;
	std::vector<Body*> m_vecBody{};

	std::vector<float> varVec{};
};


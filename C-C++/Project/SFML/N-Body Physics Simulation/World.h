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

private:
	int m_nBody;

	Body* m_body;
	std::vector<Body*> m_vecBody{};

	float m_r1Temp;
	float m_r2Temp;
	float m_x1Temp;
	float m_x2Temp;
	float m_y1Temp;
	float m_y2Temp;
	float m_dx1Temp;
	float m_dx2Temp;
	float m_dy1Temp;
	float m_dy2Temp;
	float m_m1Temp;
	float m_m2Temp;
};


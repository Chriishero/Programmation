#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include "Renderer.h"
#include "body.h"
#include <string>

class World
{
public:
	World(int nBody, float timeScale, std::string approximationMethod);

	void create();
	void setGui(tgui::GuiSFML &gui);
	sf::Vector2f newtonRaphsonMethod(sf::Vector2f acceleration, sf::Vector2f velocity, sf::Vector2f position);
	std::vector<sf::Vector2f> computeAcceleration(std::vector<sf::Vector2f> velocities = {}, std::vector<sf::Vector2f> positions = {});
	void motion(float deltaTime);
	void update(float deltaTime);
	void render(Renderer& renderer);

	float M_PI = 3.14159265358979323846f;

private:
	int m_nBody;
	float m_timeScale;
	std::string m_approximationMethod;

	float m_distMin = 100.0f;
	float m_distMax = 1000.0f;
	float m_angleMin = 0.0f;
	float m_angleMax = 2 * M_PI;
	float m_massMin = 1e22f;
	float m_massMax = 1e24f;
	float m_centralRadius = 10.0f;
	float m_centralMass = 1e30f;
	float m_pixelToMeter = 1e9;

	Body* m_body;
	std::vector<Body*> m_vecBody{};

	std::vector<float> varVec{};
};


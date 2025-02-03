#pragma once

#include "renderer.hpp"
#include "resources.hpp"

class Object
{
public:
	virtual void begin() {}
	virtual void update(float deltaTime) {}
	virtual void render(Renderer& renderer) {}

	std::string tag;

	sf::Vector2f position;
	float angle;
};


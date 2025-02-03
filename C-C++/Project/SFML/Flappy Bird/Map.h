#pragma once

#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#include "resources.hpp"
#include "Pipe.h"
#include <vector>
#include "Object.h"

class Map
{
public:
	Map();

	void generateMap();
	void update(float deltaTime);
	void draw(Renderer& renderer);

	std::vector<Pipe*> getPipe();
	std::vector<float> getPipePosition();

private:
	Pipe* m_pipe;
	float m_pipeDeltaTime = 0;
	std::vector<Pipe*> m_pipeListe;
	std::vector<float> m_yPos;
};


#pragma once
#include <vector>
#include "Rode.h"
#include "Renderer.h"

class World
{
public:
	World(int nRod);

	void create();
	void update(float deltaTime);
	void render(Renderer& renderer);

private:
	int m_nRod;
	Rode* m_rod;
	std::vector<Rode*> m_vecRod{};
};


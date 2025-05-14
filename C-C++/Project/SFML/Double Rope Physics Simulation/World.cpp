#include "World.h"

World::World(int nRod) : m_nRod(nRod)
{
}

void World::create()
{
	for (int i = 0; i < 2; i++) {
		if(m_vecRod.empty())
			m_rod = new Rode(sf::Vector2f(30, 250), sf::Vector2f(920 / 2, 920 / 2), sf::Vector2f(5, 5), 50);
		else {
			auto prevPos = m_vecRod[i - 1]->getm_position();
			auto prevSize = m_vecRod[i - 1]->getm_size();
			m_rod = new Rode(prevSize, sf::Vector2f(prevPos.x, prevPos.y + prevSize.y), sf::Vector2f(5, 5), 50);
		}
		m_vecRod.push_back(m_rod);
	}
}

void World::update(float deltaTime)
{
	for (auto rod : m_vecRod) {
		rod->update(deltaTime);
	}
}

void World::render(Renderer& renderer)
{
	for (auto rod : m_vecRod) {
		rod->draw(renderer);
	}
}

#include "Map.h"
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()

float startSpace = 5.0f;
float pipeSpace = 6.5f;

Map::Map()
{
}

void Map::generateMap()
{
	std::srand(std::time(0));

	int min = 12;
	int max = 17;
	for (size_t x = 0; x < 100; x++)
	{
		m_pipe = new Pipe();

		float y = min + std::rand() % (max - min + 1);
		m_yPos.push_back(y);

		m_pipe->position = sf::Vector2f(pipeSpace * x + startSpace, y);

		m_pipeListe.push_back(m_pipe);
		
		m_pipe->begin();
	}

	min = -17;
	max = -12;
	for (size_t x = 0; x < 100; x++)
	{
		m_pipe = new Pipe();

		float y = min + std::rand() % (max - min + 1);
		m_yPos.push_back(y);

		m_pipe->position = sf::Vector2f(pipeSpace * x + startSpace, y);
		m_pipe->angle = 110 * (180.0f / M_PI);

		m_pipeListe.push_back(m_pipe);

		m_pipe->begin();
	}
}

void Map::update(float deltaTime)
{
	for (const auto& pipe : m_pipeListe)
	{
		pipe->update(deltaTime);
	}   
}

void Map::draw(Renderer& renderer)
{
	for (const auto& pipe : m_pipeListe)
	{
		pipe->render(renderer);
	}
}

std::vector<Pipe*> Map::getPipe()
{
	return m_pipeListe;
}

std::vector<float> Map::getPipePosition()
{
	std::vector<float> xPosList;

	for (auto const& pipe : m_pipeListe)
	{
		if(pipe->angle == 110 * (180.0f / M_PI))
		{
			xPosList.push_back(pipe->position.x);
		}
	}
	return xPosList;
}

#include "Game.h"
#include "Resources.h"
#include "Physics.h"
#include "Map.h"
#include "Character.h"
#include "Object.h"
#include <filesystem>
#include <algorithm>
#include <vector>

Map map("Final Destination");
Camera camera(20.0f);
Character mario("Mario");
Character link("Link");

bool paused = false;
bool title = true;
bool coutDown = false;
int coutDownN = 10;
float currentCount = 0;

sf::Font font{};

sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));

void restart()
{
	Physics::init();

	paused = false;
	title = true;

	mario = Character("Mario");
	mario.begin();

	link = Character("Link");
	link.begin();

	map = Map("Final Destination");
	map.begin();
}


void begin()
{
	for (auto& directory : std::filesystem::directory_iterator("./res/sprites/"))
	{
		if (directory.is_directory())
		{
			for (auto& file : std::filesystem::directory_iterator("./res/sprites/" + directory.path().filename().string()))
			{
				if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
				{
					Resources::textures[directory.path().filename().string() + "/" + file.path().filename().string()].loadFromFile(file.path().string());
				}
			}
		}
	}
	for (auto sprite : Resources::textures)
	{
		std::cout << sprite.first << std::endl;
	}

	for (auto& file : std::filesystem::directory_iterator("./res/audio/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".wav" || file.path().extension() == ".ogg"))
		{
			Resources::sounds[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}
	font.loadFromFile("./res/font.ttf");

	backgroundShape.setFillColor(sf::Color(0, 0, 0, 155));
	backgroundShape.setOrigin(0.5f, 0.5f);

	restart();
}

void update(float deltaTime)
{
	Physics::update(deltaTime);
	map.update(deltaTime);
	mario.update(deltaTime);
	link.update(deltaTime);
}

void render(Renderer& renderer)
{
	map.draw(renderer, camera.getm_position(), camera.getm_viewSize());
	mario.draw(renderer);
	link.draw(renderer);

	Physics::DebugDraw(renderer);
}

void renderUI(Renderer& renderer)
{
}

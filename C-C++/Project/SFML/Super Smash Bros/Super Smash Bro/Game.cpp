#include "Game.h"
#include "Resources.h"
#include "Physics.h"
#include "Map.h"
#include "Object.h"
#include "Menu.h"
#include <filesystem>
#include <algorithm>
#include "Character.h"

Menu menu;
Map map("Final Destination");
Camera camera(25.0f);
Character mario("Mario");
Character link("Link");

bool paused = false;
bool menuState = true;

sf::Font font{};

sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));

void restart()
{
	Physics::init();

	paused = false;
	menuState = true;

	menu = Menu();
	menu.begin();

	if (!menuState)
	{
		mario.begin();
		link.begin();

		std::cout << "Load map : " << std::endl;
		map = Map("Final Destination");
		map.begin();
	}
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
	if(!menuState)
	{
		Physics::update(deltaTime);
		map.update(deltaTime);
;
		link.update(deltaTime);
		mario.update(deltaTime);
	}
}

void updateUI(float deltaTime, sf::Event event)
{
	if(menuState)
	{
		menu.update(deltaTime, event, camera.getm_viewSize(), camera.getm_position());
	}
}

void render(Renderer& renderer)
{
	if (!menuState)
	{
		map.draw(renderer, camera.getm_position(), camera.getm_viewSize());
		
		link.draw(renderer);
		mario.draw(renderer);

		Physics::DebugDraw(renderer);
	}
}

void renderUI(Renderer& renderer)
{
	if (menuState)
	{
		menu.draw(renderer);
	}
}

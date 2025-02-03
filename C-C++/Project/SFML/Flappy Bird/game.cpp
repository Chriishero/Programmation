#include "game.hpp"
#include "resources.hpp"
#include "Physics.h"
#include "Map.h"
#include "bird.h"
#include "Pipe.h"
#include <SFML/Audio.hpp>
#include <filesystem>

Map map{};
Camera camera(20.0f);
Bird bird;

bool paused = false;
bool title = true;
bool gameover = false;
bool countdown = false;
int coutdownN = 10;
float currentCount = 0;

int score;
int previousScore = 0;

sf::Font font{};
sf::Text scoreText("Score", font);
sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));

void restart()
{
	Physics::init();

	gameover = false;
	paused = false;
	title = true;

	bird = Bird();
	bird.isDead = false;
	bird.begin();

	map = Map();
	map.generateMap();

	std::cout << "title : " << title << "\npaused : " << paused << std::endl;
}

void begin()
{
	for (auto& file : std::filesystem::directory_iterator("./res/sprites/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
		{
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}
	for (auto& file : std::filesystem::directory_iterator("./res/audio/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".ogg" || file.path().extension() == ".wav"))
		{
			Resources::sounds[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	font.loadFromFile("./res/font.ttf");
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setOutlineThickness(1.0f);
	scoreText.setScale(0.2f, 0.2f);

	backgroundShape.setFillColor(sf::Color(0, 0, 0, 155));
	backgroundShape.setOrigin(0.5f, 0.5f);

	restart();
}

int i = 0;

void update(float deltaTime)
{
	if (countdown)
	{
		if (coutdownN == 0)
		{
			coutdownN = 9;
			countdown = false;
		}

		currentCount += deltaTime;
		std::cout << " coutdown : " << currentCount << std::endl;
		if (currentCount >= 1)
		{
			coutdownN--;
			currentCount = 0;
		}
	}
	if (title && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		title = false;
		countdown = true;
		return;
	}
	if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		restart();
		return;
	}
	if (bird.isDead)
	{
		gameover = true;
	}

	if (title || gameover || paused || countdown)
	{
		return;
	}

	Physics::update(deltaTime);
	bird.update(deltaTime);
	map.update(deltaTime);

	previousScore = score;
	score = 0;
	for (auto const& pos : map.getPipePosition())
	{
		if (bird.position.x > pos)
		{
			score++;
		}
	}
	if (score % 5 == 0 && previousScore < score)
	{
		for (const auto& pipe : map.getPipe())
		{
			pipe->setMovementSpeed(pipe->getMovementSpeed() + 0.5f);
		}
	}
	std::cout << "score : " << score << std::endl;
}

void render(Renderer& renderer)
{
	renderer.draw(Resources::textures["background-day.png"], camera.getposition(), camera.getViewSize());

	map.draw(renderer);
	bird.draw(renderer);

	Physics::DebugDraw(renderer);
}

void renderUI(Renderer& renderer)
{
	scoreText.setPosition(-camera.getViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
	scoreText.setString("Score : " + std::to_string(score));
	renderer.target.draw(scoreText);

	if (paused)
	{
		backgroundShape.setScale(camera.getViewSize());
		renderer.target.draw(backgroundShape);
	}
	if (gameover)
	{
		backgroundShape.setScale(camera.getViewSize());
		renderer.target.draw(backgroundShape);
		renderer.draw(Resources::textures["gameover.png"], camera.getposition(), sf::Vector2f(100.0f, 20.0f));
	}
	if (title)
	{
		backgroundShape.setScale(camera.getViewSize());
		renderer.target.draw(backgroundShape);
		renderer.draw(Resources::textures["message.png"], camera.getposition(), sf::Vector2f(100.0f, 100.0f));
	}
	if (countdown)
	{
		backgroundShape.setScale(camera.getViewSize());
		renderer.target.draw(backgroundShape);
		if(coutdownN == 10)
		{
			renderer.draw(Resources::textures[std::to_string(1) + ".png"], 
				sf::Vector2f(camera.getposition().x - 12.5f, camera.getposition().y), sf::Vector2f(30.0f, 30.0f));
			renderer.draw(Resources::textures[std::to_string(0) + ".png"],
				sf::Vector2f(camera.getposition().x + 12.5f, camera.getposition().y), sf::Vector2f(30.0f, 30.0f));
		}
		else
		{
			renderer.draw(Resources::textures[std::to_string(coutdownN) + ".png"], camera.getposition(), sf::Vector2f(30.0f, 30.0f));
		}
	}
}

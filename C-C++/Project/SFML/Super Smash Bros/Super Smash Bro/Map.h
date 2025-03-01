#pragma once

#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Renderer.h"
#include "Resources.h"
#include <vector>
#include <box2d/box2d.h>
#include "Animation.h"

class Map : public ContactListener
{
public:
	Map(std::string name);

	void loadAnimation();
	void loadSprites();
	std::vector<b2Vec2> getFixtureSize(sf::Texture texture);
	void createShape(sf::Vector2f size, std::vector<b2Vec2> vertices);
	void begin();
	void update(float deltaTime);
	void draw(Renderer& renderer, sf::Vector2f position, sf::Vector2f size);

	// Hérité via ContactListener
	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void onEndContact(b2Fixture* self, b2Fixture* other) override;

	std::string getm_name();
	
	sf::Vector2f stagePosition; 
	sf::Vector2f stageSize = sf::Vector2f(10.0f, 10.0f);
	sf::Vector2f previousStageSize; 

private:
	std::string m_name;
	float m_spritePos;

	FixtureData fixtureData{};
	b2Body* body;
	std::vector<sf::RenderTexture*> renderList;
	std::map<std::string, Animation> animations{};

	sf::Texture textureToDraw{};
};


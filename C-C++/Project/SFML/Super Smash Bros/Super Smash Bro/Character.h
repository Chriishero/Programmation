#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/b2_body.h>
#include "Animation.h"
#include "Renderer.h"
#include "Physics.h"
#include "Resources.h"
#include <map>
#include <string>

class Character : public ContactListener
{
public:
	Character(sf::String name);

	void loadAnimation();
	void loadSprites();
	void createShape(sf::Vector2f size);
	void begin();

	void update(float deltaTime);
	void draw(Renderer& renderer);

	void takeDamage(float xDamage, float yDamage, float life);

	// Hérité via ContactListener
	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void onEndContact(b2Fixture* self, b2Fixture* other) override;

	sf::Vector2f position = sf::Vector2f(0.0f, -5.0f);
	sf::Vector2f size = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f previousSize = sf::Vector2f(0.0f, 0.0f);

	float yPosition = 0.0f;

private:
	sf::String m_name;
	std::vector<std::string> animationNames = { "stand", "jump", "running", "attacks", "uptilt", "downtilt",
										"smash", "tilt", "aerial", "damage", "guarding", "win", "loose" };

	std::map<std::string, Animation> animations{};
	std::map<std::string, bool> animationsKeyPress{};
	std::map<std::string, int> animationsFrame{};

	sf::Texture textureToDraw{};

	FixtureData fixtureData{};
	b2Body* body{};
	b2Fixture* groundFixture;
	b2Fixture* bodyFixture;
	std::vector<sf::RenderTexture*> renderList;

	float previousYPosition = 0;

	bool m_facingLeft{};
	bool isGrounded = true;
	bool characterContact = false;

	bool damaged = false;
	bool knockback = false;

	bool landing = false;
	bool aerial = false;
	bool run = false;

	bool attacks = false;
	
	bool win = false;

	float m_lifePourcentage = 1;
	float m_attacksPoint = 0.05;

	float m_baseXDamage = 3.0f;
	float m_baseYDamage = -1.5f;
	float m_xDamageVelocity = m_baseXDamage;
	float m_yDamageVelocity = m_baseYDamage;

	float m_forceLoad = 1.0f;

};


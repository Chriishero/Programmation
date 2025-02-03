#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include "renderer.hpp"
#include "resources.hpp"
#include "Physics.h"
#include "Animation.h"
#include <iostream>

class Bird : public ContactListener
{
public:
	void begin();
	void update(float deltaTime);
	void draw(Renderer& renderer);

	// Hérité via ContactListener
	void OnBeginContact() override;
	void OnEndContact() override;

	sf::Vector2f position{};
	float angle{};
	bool isDead{};

private:
	int score;

	sf::Texture textureToDraw{};
	sf::Sound flySound{};

	Animation flyAnimation;
	b2Body* body{};
};


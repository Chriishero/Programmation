#pragma once

#include <box2d/box2d.h>
#include "Renderer.h"

constexpr float M_PI = 22.0f / 7.0f;

class MyDebugDraw;
class Character;
class Map;

class ContactListener
{
public:
	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) = 0;
	virtual void onEndContact(b2Fixture* self, b2Fixture* other) = 0;
};

enum class FixtureDataType
{
	Character,
	Map
};

struct FixtureData
{
	FixtureDataType type;
	ContactListener* listener;

	union
	{
		Character* character;
		Map* map;
	};
};

class Physics
{
public:
	static void init();
	static void update(float deltaTime);
	static void DebugDraw(Renderer& renderer);

	static b2World* world;
	static MyDebugDraw* debugDraw;
};


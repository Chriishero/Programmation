#pragma once
#include <box2d/box2d.h>
#include "renderer.hpp"

constexpr float M_PI = 22.0f / 7.0f;

class MyDebugDraw;

class ContactListener
{
public:
	virtual void OnBeginContact() = 0;
	virtual void OnEndContact() = 0;
};

class Physics
{
public:
	static void init();
	static void update(float deltaTime);
	static void DebugDraw(Renderer& renderer);
	
	static b2World* world;
	static MyDebugDraw* debugDraw;
private:

};


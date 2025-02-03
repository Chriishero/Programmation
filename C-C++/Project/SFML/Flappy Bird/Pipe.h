#pragma once

#include "Object.h"
#include "Physics.h"
#include <box2d/box2d.h>
class Pipe : public Object
{
public:
	~Pipe();

	virtual void begin() override;
	virtual void update(float deltaTime) override;
	virtual void render(Renderer& renderer) override;

	float getMovementSpeed();
	void setMovementSpeed(float n);

private:
	b2Body* body;
	float movementSpeed = 10.0f;
};


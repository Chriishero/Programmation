#include "Pipe.h"
#include "game.hpp"

Pipe::~Pipe()
{

}

void Pipe::begin()
{
	tag = "pipe";

	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(2.0f / 2.0f, 20.0f / 2.0f);

	b2FixtureDef fixtureDef{};
	fixtureDef.userData.pointer = (uintptr_t)this;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0.0f;
	body->CreateFixture(&fixtureDef);
}

void Pipe::update(float deltaTime)
{
	b2Vec2 velocity = body->GetLinearVelocity();

	velocity.x = -movementSpeed;
	body->SetLinearVelocity(velocity);	

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
}

void Pipe::render(Renderer& renderer)
{
	renderer.draw(Resources::textures["pipe-green.png"], position, sf::Vector2f(2.0f, 20.0f), angle);
}

float Pipe::getMovementSpeed()
{
	return movementSpeed;
}

void Pipe::setMovementSpeed(float n)
{
	movementSpeed = n;
}

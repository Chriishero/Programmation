#include "bird.h"

const float flyVelocity = 5.0f;

void Bird::begin()
{
	flyAnimation = Animation(0.45f,
		{
			AnimFrame(0.30f, Resources::textures["yellowbird-upflap.png"]),
			AnimFrame(0.15f, Resources::textures["yellowbird-midflap.png"]),
			AnimFrame(0.00f, Resources::textures["yellowbird-downflap.png"])
		});

	flySound.setBuffer(Resources::sounds["wing.wav"]);
	flySound.setVolume(20);
	
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};
	fixtureDef.userData.pointer = (uintptr_t)this;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;

	b2CircleShape circleShape{};
	circleShape.m_radius = 2.5f / 2.0f;
	circleShape.m_p.Set(0.0f, 0.0f);
	fixtureDef.shape = &circleShape;
	fixtureDef.isSensor = false;
	body->CreateFixture(&fixtureDef);

	b2CircleShape sensorCircleShape{};
	sensorCircleShape.m_radius = 2.5f / 2.0f;
	sensorCircleShape.m_p.Set(0.0f, 0.0f);
	fixtureDef.shape = &sensorCircleShape;
	fixtureDef.isSensor = true;
	body->CreateFixture(&fixtureDef);

}

void Bird::update(float deltaTime)
{
	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0.0f;

	flyAnimation.update(deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y = -flyVelocity;
		flySound.play();
		textureToDraw = flyAnimation.getTexture();
	}
	else
	{
		textureToDraw = Resources::textures["yellowbird-midflap.png"];
	}

	body->SetLinearVelocity(velocity);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
}

void Bird::draw(Renderer& renderer)
{
	renderer.draw(textureToDraw, position, sf::Vector2f(2.5f, 2.5f), angle);
}

void Bird::OnBeginContact()
{
	std::cout << "touché" << std::endl;
	isDead = true;
}

void Bird::OnEndContact()
{
}

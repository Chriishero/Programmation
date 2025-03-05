#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include "Animation.h"
#include "Renderer.h"
#include "Physics.h"
#include "Resources.h"
#include <map>
#include <string>

class Character : public ContactListener
{
public:
	Character(std::string name, bool local);

	void loadAnimation();
	void loadSprites();
	void createBody();
	void createShape(sf::Vector2f size);
	void begin();

	void sendPacket(bool creation);
	void update(float deltaTime);
	void draw(Renderer& renderer);

	void takeDamage(float xDamage, float yDamage, float life);

	// Hérité via ContactListener
	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void onEndContact(b2Fixture* self, b2Fixture* other) override;

	std::string getm_name();
	bool getm_local();
	void setm_actionsState(std::vector<bool> state);
	float getm_lifePourcentage();
	void setm_lifePourcentage(float life);
	int getm_nLife();
	bool getm_defeat();
	void setm_defeat(bool state);
	bool getm_dead();
	void setm_dead(bool state);
	bool getm_win();
	void setm_win(bool state);
	void setm_nLife(int n);

	/*struct CharacterData
	{
		char name[32];
		sf::Vector2f position;
		sf::Texture texture;
		sf::Vector2f size;
		bool creation;
	};
	struct CharacterData
	{
		char name[32];
		Character* player;
		bool creation;
		bool loading;
	};*/
	struct CharacterData
	{
		char name[32];
		char mapName[64];
		//std::vector<uint32_t> actionsState;
		//sf::Texture texture;

		bool smash;
		bool tilt;
		bool down;
		bool guarding;
		bool right;
		bool left;
		bool up;
		bool attacks;

		float lifePourcentage;
		int nLife;
		sf::Vector2f position;


		bool defeat;
	};

	sf::Texture textureToDraw{};
	sf::Vector2f position = sf::Vector2f(0.0f, -5.0f);
	sf::Vector2f size = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f previousSize = sf::Vector2f(0.0f, 0.0f);

	float yPosition = 0.0f;

	bool isLoading = true;


private:
	bool m_local;
	std::string m_name;

	CharacterData m_characterData;

	std::vector<std::string> animationNames = { "stand", "jump", "running", "attacks", "upaerial", "downtilt",
										"smash", "tilt", "aerial", "damage", "guarding", "win", "loose", "uptilt" };

	std::map<std::string, Animation> animations{};
	std::map<std::string, bool> animationsKeyPress{};
	std::map<std::string, int> animationsFrame{};

	struct ActionsState
	{
		sf::Keyboard::Key key;
		bool pressed;
	};

	std::vector<bool> m_actionsState{};
	std::map<std::string, ActionsState> actions{ {"smash", {sf::Keyboard::B, false}},
												{"tilt", {sf::Keyboard::V, false}},
												{"down", {sf::Keyboard::Down, false}},
												{"guarding", {sf::Keyboard::X, false}},
												{"right", {sf::Keyboard::Right, false}},
												{"left", {sf::Keyboard::Left, false}},
												{"up", {sf::Keyboard::Up, false}},
												{"attacks", {sf::Keyboard::C, false}} };
				

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
	bool guardingState = false;
	float guarding = 5.0f;

	bool landing = false;
	bool aerial = false;
	bool upaerial = false;
	bool run = false;
	int upAerialUtilisation = 0;

	bool attacks = false;
	bool aerialattacks = false;
	
	bool m_win = true;
	bool m_defeat = false;
	bool m_dead = false;

	int m_nLife = 4;
	float m_lifePourcentage = 1.0f;
	float m_prevLife = m_lifePourcentage;
	float m_attacksPoint = 0.05f;
	float m_forceDemultiplication = 1.0f;

	float m_baseXDamage = 2.0f;
	float m_baseYDamage = -4.0f;
	float m_xDamageVelocity = m_baseXDamage;
	float m_yDamageVelocity = m_baseYDamage;

	float m_xKBScaling = 1.0f;
	float m_yKBScaling = 1.0f;

	int nGameOverUpdate = 0;
};


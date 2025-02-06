#include "Character.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <filesystem>
#include <math.h>

const float runVelocity = 3.0f;
const float jumpVelocity = 10.0f;

Character::Character(sf::String name) : m_name(name)
{
}

void Character::loadAnimation()
{
	for (auto animationName : animationNames)
	{
		std::vector<sf::Texture> textures{};
		std::cout << animationName << " : " << std::endl;
		for (auto texture : Resources::textures)
		{
			std::string stardWith = m_name + "/" + animationName;
			if (texture.first.starts_with(stardWith))
			{
				std::cout << "	" << texture.first << std::endl;

				textures.push_back(texture.second);
			}
		}
		//std::reverse(standTextures.begin(), standTextures.end());
		std::cout << "textyres size : " << textures.size() << std::endl;

		std::vector<AnimFrame> frames{};
		for (size_t i = 0; i < textures.size(); i++)
		{
			auto animFrame = AnimFrame(i * 0.15f, textures[i]);
			frames.push_back(animFrame);
		}
		std::reverse(frames.begin(), frames.end());
		animations[animationName] = Animation(0.15f * textures.size(), frames);
		std::cout << "taille frames : " << frames.size() << std::endl;
	}
	std::cout << "name animations : " << std::endl;
	for (auto name : animations)
	{
		std::cout << "	" << name.first << std::endl;
	}
}

void Character::loadSprites()
{
	for (auto& directory : std::filesystem::directory_iterator("./res/sprites/"))
	{
		if (directory.is_directory())
		{
			for (auto& file : std::filesystem::directory_iterator("./res/sprites/" + directory.path().filename().string()))
			{
				if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
				{
					Resources::textures[directory.path().filename().string() + "/" + file.path().filename().string()].loadFromFile(file.path().string());
				}
			}
		}
	}
}

void Character::createShape(sf::Vector2f size)
{
	fixtureData.listener = this;
	fixtureData.character = this;
	fixtureData.type = FixtureDataType::Character;

	b2FixtureDef fixtureDef{};
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(size.x / 2 - size.x * 0.1, size.y / 2);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(size.x / 2 + size.x * 0.1, size.y / 2);
	fixtureDef.isSensor = true;
	bodyFixture = body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(0.2f, 0.2f, b2Vec2(0.0f, 2.0f), 0.0f);
	fixtureDef.isSensor = true;
	groundFixture = body->CreateFixture(&fixtureDef);
}

void Character::begin()
{
	sf::Texture marioSheet = Resources::textures["Sheet/" + m_name + ".png"];
	sf::Image imageMarioSheet = marioSheet.copyToImage();
	sf::Vector2u sheetSize = imageMarioSheet.getSize();

	sf::RenderTexture* spriteRenderTexture;

	std::vector<std::string> animName = animationNames;
	std::reverse(animName.begin(), animName.end());

	int emptyLine = 0;
	int nSprite = 0;
	int spriteSize = 0;
	for (auto y = 0; y < sheetSize.y; y++)
	{
		for (auto x = 0; x < sheetSize.x; x++)
		{
			if (imageMarioSheet.getPixel(x, y).a != 0)
			{
				emptyLine = 0;

				sf::Image pixelN;
				pixelN.create(1, 1, imageMarioSheet.getPixel(x, y));

				sf::Texture texturePixel;
				texturePixel.loadFromImage(pixelN);

				sf::Sprite spritePixel;
				spritePixel.setTexture(texturePixel);
				spritePixel.setPosition(x, y);

				spriteRenderTexture = new sf::RenderTexture();
				spriteRenderTexture->draw(spritePixel);
				spriteRenderTexture->create(sheetSize.x, sheetSize.y);

				imageMarioSheet.setPixel(x, y, sf::Color(0, 0, 0, 0));

				int sx = x;
				int sy = y;
				
				std::vector<std::vector<int>> previousPos;
				previousPos.push_back({sx, sy});

				int left = x;
				int top = y;
				int right{};
				int bottom{};

				bool firstPixel = false;

				const int offsets[8][2] = {
					{0, 1}, {0, -1},
					{1, 0}, {1, 1}, {1, -1},
					{-1, 0}, {-1, 1}, {-1, -1}
				};
				while (1)
				{
					bool foundPixel = false;

					for (auto offset : offsets) 
					{
						int newSX = sx + offset[0];
						int newSY = sy + offset[1];

						if (imageMarioSheet.getPixel(newSX, newSY).a != 0)
						{
							sx = newSX;
							sy = newSY;
							previousPos.push_back({ sx, sy });

							if (!firstPixel || sx > right)
							{
								firstPixel = true;
								right = sx;
							}
							if (!firstPixel || sy > bottom)
							{
								firstPixel = true;
								bottom = sy;
							}
							if (!firstPixel || sx < left)
							{
								firstPixel = true;
								left = sx;
							}
							if (!firstPixel || sy < top)
							{
								firstPixel = true;
								top = sy;
							}

							pixelN.create(1, 1, imageMarioSheet.getPixel(sx, sy));
							texturePixel.loadFromImage(pixelN);
							spritePixel.setTexture(texturePixel);
							spritePixel.setPosition(sx, sy);
							spriteRenderTexture->draw(spritePixel);
							imageMarioSheet.setPixel(sx, sy, sf::Color(0, 0, 0, 0));

							//std::cout << "Nouveau pixel trouvé. : (" << sx << ";" << sy << ")" << std::endl;
							foundPixel = true;
						}
					}
					if (!foundPixel)
					{
						previousPos.pop_back();
						if (previousPos.empty())
						{
							break;
						}
						auto prev = previousPos.back();
						sx = prev[0];
						sy = prev[1];
					}
				}
				spriteRenderTexture->display();
				sf::Sprite characterSprite;
				characterSprite.setTexture(spriteRenderTexture->getTexture());

				spriteSize = bottom - top + 1;
				sf::IntRect spriteBounds(left, top, right-left+1, spriteSize);
				characterSprite.setTextureRect(spriteBounds);

				spriteRenderTexture = new sf::RenderTexture();
				spriteRenderTexture->create(spriteBounds.width, spriteBounds.height);
				spriteRenderTexture->draw(characterSprite);
				renderList.push_back(spriteRenderTexture);

				nSprite++;
				continue;
			}
			else
			{
				bool foundPixel = false;
				for (size_t i = 0; i < 8; i++)
				{
					if (y + i < sheetSize.y && imageMarioSheet.getPixel(x, y + i).a != 0)
					{
						foundPixel = true;
						y += i;
						break;
					}
				}
				if (foundPixel)
				{
					break;
				}
			}
		}
		emptyLine++;
		if (emptyLine > spriteSize / 3)
		{
			if(!renderList.empty())
			{
				for (size_t i = 0; i < renderList.size(); i++)
				{
					renderList[i]->display();
					sf::Texture marioTexture = renderList[i]->getTexture();
					sf::Sprite spriteToDisplay;
					spriteToDisplay.setTexture(marioTexture);

					sf::Image image = marioTexture.copyToImage();
					image.saveToFile("res/sprites/" + m_name + "/" + animName.back() + "-" + std::to_string(i) + ".png");

				}
				std::cout << renderList.size() << " : " << animName.back() << std::endl;
				renderList.clear();
				animName.pop_back();
			}
		}
	}

	loadSprites();
	loadAnimation();

	for (auto name : animationNames)
	{
		animationsKeyPress[name] = false;
		animationsFrame[name] = animations[name].getm_frames().size()-1;
		std::cout << std::string(m_name) << " : " << name << " : " << animationsFrame[name] << std::endl;
	}
	animationsFrame["guarding"] = 2;
	animationsFrame["upaerial"] = 1;

	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	createShape(sf::Vector2f(0.5f, 0.5f));
}

void Character::update(float deltaTime)
{
	float xSpeed = runVelocity;
	float ySpeed = jumpVelocity;

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0.0f;

	if(!damaged)
	{
		if (knockback)
		{
			for (auto animation : animations)
			{
				if (animation.first != "damage")
					animation.second.setm_time(0.0f);
			}
			animations["damage"].update(deltaTime);
			textureToDraw = animations["damage"].getTexture();

			auto frames = animations["damage"].getm_frames();
			if (animations["damage"].getm_time() >= frames[0].time)
			{
				std::cout << std::string(m_name) << " : knockack off" << std::endl;
				knockback = false;
				animations["damage"].setm_time(0.0f);
			}
		}
		else
		{
			auto updateReleasedFrames = [this, deltaTime](std::string name) -> void
				{
					if (!animationsKeyPress[name])
					{
						animations[name].update(deltaTime);
						if (m_xKBScaling > 1.0f || m_yKBScaling > 1.0f)
						{
							std::cout << "attacks ! " << std::endl;
						}
					}
					textureToDraw = animations[name].getTexture();

					auto frames = animations[name].getm_frames();
					if (animations[name].getm_time() >= frames[animationsFrame[name]].time)
					{
						animationsKeyPress[name] = true;
					}
				};

			bool keyPress = false;
			sf::Keyboard::Key key;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				if (!landing)
				{
					if (m_xKBScaling <= 5.0f)
					{
						m_xKBScaling += 0.035f;
						m_yKBScaling += 0.025f;
						m_forceDemultiplication += 0.015;
					}
					std::cout << "smash force load : " << m_xKBScaling << " & " << m_yKBScaling << std::endl;
					updateReleasedFrames("smash");
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) &&
				(sf::Keyboard::isKeyPressed(key = sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(key = sf::Keyboard::Left)))
			{
				if (!landing)
				{
					if (m_xKBScaling <= 4.0f)
					{
						m_xKBScaling += 0.03f;
						m_yKBScaling += 0.03f;
						m_forceDemultiplication += 0.015;
					}

					m_facingLeft = (key == sf::Keyboard::Right) ? false : true;
					updateReleasedFrames("tilt");
					std::cout << "tilt force load : " << m_xKBScaling << " & " << m_yKBScaling << std::endl;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) &&
				(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
			{
				if (!landing)
				{
					if (m_yKBScaling <= 8.0f)
					{
						m_xKBScaling += 0.01f;
						m_yKBScaling += 0.05;
						m_forceDemultiplication += 0.015;
					}

					updateReleasedFrames("uptilt");
					std::cout << "uptilt force load : " << m_xKBScaling << " & " << m_yKBScaling << std::endl;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) &&
				(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			{
				if (!landing)
				{
					if (m_xKBScaling <= 4.0f)
					{
						m_xKBScaling += 0.035f;
						m_yKBScaling += 0.025f;
						m_forceDemultiplication += 0.015;
					}

					updateReleasedFrames("downtilt");
					std::cout << "downtilt force load : " << m_xKBScaling << " & " << m_yKBScaling << std::endl;
				}
			}

			else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				if(!landing)
					updateReleasedFrames("guarding");
			}

			else if (win)
			{
				animations["win"].update(deltaTime);
				textureToDraw = animations["win"].getTexture();
			}
			else
			{
				for (auto name : animationNames)
				{
					if (animationsKeyPress[name])
					{
						keyPress = true;
						auto previousTime = animations[name].getm_time();

						animations[name].update(deltaTime);
						textureToDraw = animations[name].getTexture();

						if (name != "guarding")
						{
							attacks = true;
						}

						if (animations[name].getm_time() < previousTime)
						{
							animationsKeyPress[name] = false;
						}
					}
				}
				if (!keyPress)
				{
					attacks = false;
					run = false;
					m_xKBScaling = 1.0f;
					m_yKBScaling = 1.0f;
					if (sf::Keyboard::isKeyPressed(key = sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(key = sf::Keyboard::Left))
					{
						run = true;
						m_facingLeft = (key == sf::Keyboard::Right) ? false : true;
						velocity.x += (key == sf::Keyboard::Right) ? xSpeed : -xSpeed;

						animations["running"].update(deltaTime);
						textureToDraw = animations["running"].getTexture();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						if (isGrounded)
						{
							velocity.y = -ySpeed;
							landing = true;
						}
						textureToDraw = animations["jump"].getTexture();
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::C))
					{
						if (isGrounded && !run)
						{
							animations["attacks"].update(deltaTime);
							textureToDraw = animations["attacks"].getTexture();
							attacks = true;

							m_xKBScaling = 0.2f;
							m_yKBScaling = 0.4f;

							if (m_forceDemultiplication > 0.15f)
								m_forceDemultiplication = 0.15f;
							else if (m_forceDemultiplication > 0.0f)
								m_forceDemultiplication -= 0.01f;
							else
								m_forceDemultiplication = 0.05f;
						}
						else if (!isGrounded && !upaerial && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
						{
							velocity.y = -ySpeed;
							aerial = false;
							upaerial = true;
							landing = false;
						}
						else if (!isGrounded && !upaerial)
						{
							aerial = true;
							upaerial = false;
							landing = false;
						}
					}
					if (landing || aerial || upaerial || damaged)
					{
						std::string name;
						if (aerial && velocity.x == 0.0f)
						{
							velocity.x += !m_facingLeft ? xSpeed - 1 : -xSpeed + 1;
							name = "aerial";
						}
						else if (damaged)
							name = "damage";
						else if (upaerial)
						{
							name = "upaerial";
						}
						else
							name = "jump";

						if ((previousYPosition < body->GetPosition().y))
						{
							if(!upaerial)
							{
								auto frames = animations[name].getm_frames();
								animations[name].update(deltaTime);
								textureToDraw = animations[name].getTexture();
								if (animations[name].getm_time() >= frames[0].time)
								{
									if (!isGrounded)
										textureToDraw = animations[name].getTexture();
								}
							}
							else
							{
								textureToDraw = animations[name].getTexture();
							}
						}
						else if ((previousYPosition > body->GetPosition().y))
						{
							textureToDraw = animations[name].getTexture();
							if (aerial || upaerial)
							{
								attacks = true;
								if (upaerial)
								{
									auto frames = animations[name].getm_frames();
									animations[name].update(deltaTime);
									textureToDraw = animations[name].getTexture();
									if (animations[name].getm_time() >= frames[0].time)
									{
										if (!isGrounded)
											textureToDraw = animations[name].getTexture();
									}
								}
							}
						}
						else
						{
							landing = false;
							aerial = false;
							upaerial = false;
							animations[name].setm_time(0.0f);
						}
					}
					if (isGrounded && !run && !attacks && !knockback)
					{
						animations["upaerial"].setm_time(0.0f);
						animations["aerial"].setm_time(0.0f);
						animations["jump"].setm_time(0.0f);

						velocity.x = 0.0f;
						animations["stand"].update(deltaTime);
						textureToDraw = animations["stand"].getTexture();
					}
				}
			}
			if (std::string(m_name) == "Link")
			{
				velocity.x = 0.0f;
				animations["stand"].update(deltaTime);
				textureToDraw = animations["stand"].getTexture();
			}
			body->SetLinearVelocity(velocity);
		}
	}

	else if(damaged)
	{
		std::cout << std::string(m_name) << " : damaged + impulse" << std::endl;
		body->ApplyLinearImpulseToCenter(b2Vec2(m_xDamageVelocity * pow(m_lifePourcentage, 2.5), m_yDamageVelocity * pow(m_lifePourcentage, 2.5)), true);
		std::cout << std::string(m_name) << " : knockack on" << std::endl;
		damaged = false;

		if(m_lifePourcentage > m_prevLife + 0.02)
			knockback = true;

		m_xDamageVelocity = m_baseXDamage;
		m_yDamageVelocity = m_baseYDamage;
	}

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	previousYPosition = body->GetPosition().y;
}

void Character::draw(Renderer& renderer)
{
	//renderer.draw(textureToDraw, position, sf::Vector2f(facingLeft ? -0.75f : 0.75f, 4.0f));
	auto textureSize = textureToDraw.getSize();
	float xRatio = 0.02f;
	float yRatio = 0.1f;

	size = sf::Vector2f(textureSize.x * xRatio, textureSize.y * yRatio);

	if(size.x != previousSize.x || size.y != previousSize.y)
	{
		auto fixtures = body->GetFixtureList();
		while (fixtures != nullptr) {
			auto next = fixtures->GetNext(); // Stocker la prochaine fixture
			body->DestroyFixture(fixtures); // Détruire l'actuelle
			fixtures = next;                // Passer à la suivante
		}

		createShape(sf::Vector2f(textureSize.x * xRatio, textureSize.y * yRatio));
		previousSize = size;
	}

	renderer.draw(textureToDraw, position, 
		sf::Vector2f(m_facingLeft ? -(float)textureSize.x* xRatio : textureSize.x * xRatio, textureSize.y * yRatio));
}

void Character::takeDamage(float xDamage, float yDamage, float life)
{
	m_xDamageVelocity = xDamage;
	m_yDamageVelocity = yDamage;
	m_prevLife = m_lifePourcentage;
	m_lifePourcentage = life;
}

void Character::onBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (!data)
		return;

	if (groundFixture == self && data->type == FixtureDataType::Map && !isGrounded)
	{
		//std::cout << "grounded" << std::endl;
		isGrounded = true;
		upaerial = false;
		landing = false;
		aerial = false;
	}
	if (bodyFixture == self && data->type == FixtureDataType::Character && !characterContact)
	{
		characterContact = true;

		if (attacks && std::string(m_name) == "Mario")
		{
			auto victim = data->character;
			victim->damaged = true;

			std::cout << std::string(victim->m_name) << " : " << victim->m_lifePourcentage*100 << "%" << std::endl;
			std::cout << std::string(m_name) << " attaque " << std::string(victim->m_name) << std::endl;
			
			float xDamage = (body->GetPosition().x < victim->body->GetPosition().x) ?
				victim->m_baseXDamage : -victim->m_baseXDamage;
			xDamage *= m_xKBScaling;
			float yDamage = victim->m_baseYDamage * m_yKBScaling;
			float life = victim->m_lifePourcentage + m_attacksPoint * m_forceDemultiplication;

			victim->takeDamage(xDamage, yDamage, life);

			m_forceDemultiplication = 1.0f;
			m_xKBScaling = 1.0f;
			m_yKBScaling = 1.0f;
			attacks = false;
		}
	}
}

void Character::onEndContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (!data)
		return;

	if (groundFixture == self && data->type == FixtureDataType::Map && isGrounded)
	{
		//std::cout << "pas Grounded" << std::endl;
		isGrounded = false;
		if (!aerial && !upaerial)
		{
			landing = true;
		}
	}
	if (bodyFixture == self && data->type == FixtureDataType::Character && characterContact)
	{
		characterContact = false;
	}
}

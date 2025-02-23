#include "Character.h"
#include "Game.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <filesystem>
#include <math.h>

const float runVelocity = 3.0f;
const float jumpVelocity = 10.0f;

Character::Character(std::string name, bool local) : m_name(name), m_local(local)
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

void Character::createBody()
{
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);
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

	polygonShape.SetAsBox(0.2f, 0.4f, b2Vec2(0.0f, size.y / 2), 0.0f);
	fixtureDef.isSensor = true;
	groundFixture = body->CreateFixture(&fixtureDef);
}

void Character::begin()
{
	bool load = false;
	if(load)
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
					previousPos.push_back({ sx, sy });

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
					sf::IntRect spriteBounds(left, top, right - left + 1, spriteSize);
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
				if (!renderList.empty())
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

	createBody();
	createShape(sf::Vector2f(0.5f, 0.5f));

	m_actionsState.assign(actions.size(), false);

	if(m_local)
	{
		sendPacket(true);
		isLoading = false;
	}
}

void Character::sendPacket(bool creation)
{
	/*strncpy_s(m_characterData.name, m_name.c_str(), sizeof(m_characterData.name) - 1);
	m_characterData.name[sizeof(m_characterData.name) - 1] = '\0';
	m_characterData.position = position;
	m_characterData.size = size;
	m_characterData.texture = textureToDraw;
	m_characterData.player = this;
	m_characterData.creation = creation;

	char data[sizeof(CharacterData)];
	memcpy(data, &m_characterData, sizeof(CharacterData));
	ENetPacket* packet = enet_packet_create(data, sizeof(data), ENET_PACKET_FLAG_RELIABLE);
	*/

	strncpy_s(m_characterData.name, m_name.c_str(), sizeof(m_characterData.name) - 1);
	m_characterData.name[sizeof(m_characterData.name) - 1] = '\0';
	m_characterData.smash = actions["smash"].pressed;
	m_characterData.tilt = actions["tilt"].pressed;
	m_characterData.down = actions["down"].pressed;
	m_characterData.guarding = actions["guarding"].pressed;
	m_characterData.right = actions["right"].pressed;
	m_characterData.left = actions["left"].pressed;
	m_characterData.up = actions["up"].pressed;
	m_characterData.attacks = actions["attacks"].pressed;

	//m_characterData.lifePourcentage = std::bit_cast<uint32_t>(m_lifePourcentage);
	m_characterData.lifePourcentage = m_lifePourcentage;
	m_characterData.position = position;

	char data[sizeof(CharacterData)];
	memcpy(data, &m_characterData, sizeof(CharacterData));
	ENetPacket* packet = enet_packet_create(data, sizeof(data), ENET_PACKET_FLAG_RELIABLE);

	/*std::vector<uint8_t> buffer;

	// Copie le nom du personnage (32 octets)
	buffer.insert(buffer.end(), m_characterData.name, m_characterData.name + 32);

	// Ajoute la taille du std::vector<uint32_t>
	uint32_t vectorSize = m_characterData.actionsState.size();
	buffer.insert(buffer.end(), reinterpret_cast<uint8_t*>(&vectorSize), reinterpret_cast<uint8_t*>(&vectorSize) + sizeof(uint8_t));

	// Ajoute chaque élément du std::vector<uint32_t>
	for (uint32_t state : m_characterData.actionsState) 
	{
		buffer.insert(buffer.end(), reinterpret_cast<uint8_t*>(&state), reinterpret_cast<uint8_t*>(&state) + sizeof(uint32_t));
	}

	ENetPacket* packet = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_RELIABLE);*/
	if (packet == NULL){
		std::cerr << "Erreur de création du paquet ENet !" << std::endl;
		return;
	}
	if (enet_peer_send(peer, 0, packet) < 0) {
		std::cerr << "Erreur lors de l'envoi du paquet ENet !" << std::endl;
	}

	// Pas nécessaire de flush ici si on est dans un environnement de boucle d'événements
	enet_host_flush(client);

	// Libérer le paquet après l'envoi
	//enet_packet_destroy(packet);
}

void Character::update(float deltaTime)
{
	//std::cout << "update de " << m_name << std::endl;
	float xSpeed = runVelocity;
	float ySpeed = jumpVelocity;

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0.0f;

	if (!damaged)
	{
		if (knockback)
		{
			std::cout << "if (knockback)" << std::endl;
			//std::cout << animations.size() << std::endl;
			/*for (auto animation : animations)
			{
				if (animation.first != "damage")
					animation.second.setm_time(0.0f);
			}*/
			std::cout << "for (auto animation : animations)" << std::endl;

			animations["damage"].update(deltaTime);
			std::cout << "animations[daùmage].update(deltaTime);" << std::endl;
			textureToDraw = animations["damage"].getTexture();
			std::cout << "textureToDraw" << std::endl;

			auto frames = animations["damage"].getm_frames();
			std::cout << "auto frames" << std::endl;
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

			if(m_local)
			{
				m_actionsState.clear();
				for (auto& action : actions)
				{
					if (sf::Keyboard::isKeyPressed(action.second.key) && window.hasFocus())
					{
						action.second.pressed = true;
					}
					else
					{
						action.second.pressed = false;
					}
					m_actionsState.push_back(action.second.pressed);
				}
			}
			else
			{
				int i = 0;
				for (auto& action : actions)
				{
					action.second.pressed = m_actionsState[i];
					i++;
				}
			}
			for (auto& action : actions)
			{
				if (action.second.pressed)
				{
					std::cout << m_name << " : " << action.first << std::endl;
				}
			}

			bool keyPress = false;
			sf::Keyboard::Key key;
			if (actions["smash"].pressed)
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
			else if (actions["tilt"].pressed &&
				(actions["right"].pressed || actions["left"].pressed))
			{
				if (!landing)
				{
					if (m_xKBScaling <= 4.0f)
					{
						m_xKBScaling += 0.03f;
						m_yKBScaling += 0.03f;
						m_forceDemultiplication += 0.015;
					}

					m_facingLeft = (actions["right"].pressed) ? false : true;
					updateReleasedFrames("tilt");
					std::cout << "tilt force load : " << m_xKBScaling << " & " << m_yKBScaling << std::endl;
				}
			}
			else if (actions["tilt"].pressed &&
				(actions["up"].pressed))
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
			else if (actions["tilt"].pressed &&
				(actions["down"].pressed))
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

			else if (actions["guarding"].pressed)
			{
				if (!landing)
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
					if (actions["right"].pressed || actions["left"].pressed)
					{
						run = true;
						m_facingLeft = actions["right"].pressed ? false : true;
						velocity.x += (actions["right"].pressed == true) ? xSpeed : -xSpeed;

						animations["running"].update(deltaTime);
						textureToDraw = animations["running"].getTexture();
					}
					if (actions["up"].pressed)
					{
						if (isGrounded)
						{
							velocity.y = -ySpeed;
							landing = true;
						}
						textureToDraw = animations["jump"].getTexture();
					}
					if (actions["attacks"].pressed)
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
						else if (!isGrounded && !upaerial && actions["up"].pressed && upAerialUtilisation > 0)
						{
							velocity.y = -ySpeed;
							aerial = false;
							upaerial = true;
							landing = false;
							upAerialUtilisation = 0;
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
							if (!upaerial)
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
							if (aerial && !aerialattacks)
							{
								attacks = true;
								aerialattacks = true;
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
										{
											textureToDraw = animations[name].getTexture();
											upaerial = false;
											landing = true;
										}
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
			body->SetLinearVelocity(velocity);
		}
	}

	else if (damaged)
	{
		std::cout << std::string(m_name) << " : damaged + impulse" << std::endl;
		body->ApplyLinearImpulseToCenter(b2Vec2(m_xDamageVelocity * pow(m_lifePourcentage, 2.5), m_yDamageVelocity * pow(m_lifePourcentage, 2.5)), true);
		std::cout << std::string(m_name) << " : knockack on" << std::endl;
		damaged = false;

		if (m_lifePourcentage > m_prevLife + 0.02)
			knockback = true;

		m_xDamageVelocity = m_baseXDamage;
		m_yDamageVelocity = m_baseYDamage;
	}

	if (!m_local)
		body->SetTransform(b2Vec2(position.x, position.y), body->GetAngle());

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	std::cout << position.y << std::endl;
	previousYPosition = body->GetPosition().y;

	if (position.x > camera.getm_viewSize().x / 10 || position.x < -camera.getm_viewSize().x / 10 ||
		position.y > camera.getm_viewSize().y / 10 || position.y < -camera.getm_viewSize().y / 10)
	{
		m_lifePourcentage = 1.0;
		position = sf::Vector2f(0, -2);
		body->SetTransform(b2Vec2(position.x, position.y), body->GetAngle());
	}

	//if(m_name == "Mario")
	if(m_local)
		sendPacket(false);
}

void Character::draw(Renderer& renderer)
{
	//std::cout << "draw de " << m_name << std::endl;
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

	size = sf::Vector2f(m_facingLeft ? -(float)textureSize.x * xRatio : textureSize.x * xRatio, textureSize.y * yRatio);
	renderer.draw(textureToDraw, position, size);
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
		upAerialUtilisation = 1;
	}
	if (bodyFixture == self && data->type == FixtureDataType::Character && !characterContact)
	{
		characterContact = true;

		if (attacks)
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
			//printf("%s : %d/%d : %d", victim->m_name, xDamage, yDamage, life);

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

bool Character::getm_local()
{
	return m_local;
}

void Character::setm_actionsState(std::vector<bool> state)
{
	m_actionsState = state;
}

float Character::getm_lifePourcentage()
{
	return m_lifePourcentage;
}

void Character::setm_lifePourcentage(float life)
{
	m_lifePourcentage = life;
}

std::string Character::getm_name()
{
	return m_name;
}

#include "Map.h"
#include <iostream>
#include <filesystem>

Map::Map(std::string name) : m_name(name)
{
}

void Map::loadAnimation()
{
	std::vector<sf::Texture> textures{};
	std::cout << m_name << " : " << std::endl;
	for (auto texture : Resources::textures)
	{
		std::string stardWith = "Map/" + m_name;
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
	animations[m_name] = Animation(0.15f * textures.size(), frames);
}

void Map::loadSprites()
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

std::vector<b2Vec2> Map::getFixtureSize(sf::Texture texture)
{
	sf::Image mapImage = texture.copyToImage();
	sf::Vector2u mapSize = texture.getSize();

	std::vector<sf::Vector2f> fixturePoints{};

	for (auto y = 0; y < mapSize.y; y++)
	{
		if (mapImage.getPixel(0, y).a != 0)
		{
			fixturePoints.push_back(sf::Vector2f(0, y+5));
			fixturePoints.push_back(sf::Vector2f(mapSize.x, y+5));
		}
	}

	for (auto x = 0; x < mapSize.x; x++)
	{
		if (mapImage.getPixel(x, fixturePoints[0].y /2).a != 0)
		{
			fixturePoints.push_back(sf::Vector2f(x, fixturePoints[0].y / 2));
			fixturePoints.push_back(sf::Vector2f(mapSize.x - x, fixturePoints[0].y / 2));

			fixturePoints[0].x = fixturePoints[2].x;
			fixturePoints[1].x = fixturePoints[3].x;
		}
	}

	std::vector<b2Vec2> vertices;
	vertices.reserve(fixturePoints.size()); // Réserver la mémoire pour éviter des reallocations

	for (auto i = 0; i < fixturePoints.size(); i++)
	{
		if(i < 8)
			vertices.emplace_back(fixturePoints[i].x, fixturePoints[i].y);
	}

	return vertices;
}

void Map::createShape(sf::Vector2f size, std::vector<b2Vec2> vertices)
{
	fixtureData.listener = this;
	fixtureData.map = this;
	fixtureData.type = FixtureDataType::Map;

	b2PolygonShape polygonShape{};
	//polygonShape.SetAsBox(size.x / 2.0f, size.y / 2.0f - 1.0f);
	polygonShape.Set(vertices.data(), vertices.size());

	b2FixtureDef fixtureDef{};
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0.0f;
	body->CreateFixture(&fixtureDef);
}

void Map::begin()
{
	sf::Texture mapSheet = Resources::textures["Sheet/" + m_name + ".png"];
	sf::Image imageMapSheet = mapSheet.copyToImage();
	sf::Vector2u sheetSize = imageMapSheet.getSize();

	sf::RenderTexture* spriteRenderTexture;

	int nSprite = 0;
	int spriteSize = 0;
	for (auto y = 0; y < sheetSize.y; y++)
	{
		for (auto x = 0; x < sheetSize.x; x++)
		{
			if (imageMapSheet.getPixel(x, y).a != 0)
			{

				sf::Image pixelN;
				pixelN.create(1, 1, imageMapSheet.getPixel(x, y));

				sf::Texture texturePixel;
				texturePixel.loadFromImage(pixelN);

				sf::Sprite spritePixel;
				spritePixel.setTexture(texturePixel);
				spritePixel.setPosition(x, y);

				spriteRenderTexture = new sf::RenderTexture();
				spriteRenderTexture->draw(spritePixel);
				spriteRenderTexture->create(sheetSize.x, sheetSize.y);

				imageMapSheet.setPixel(x, y, sf::Color(0, 0, 0, 0));

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

						if (imageMapSheet.getPixel(newSX, newSY).a != 0)
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

							pixelN.create(1, 1, imageMapSheet.getPixel(sx, sy));
							texturePixel.loadFromImage(pixelN);
							spritePixel.setTexture(texturePixel);
							spritePixel.setPosition(sx, sy);
							spriteRenderTexture->draw(spritePixel);
							imageMapSheet.setPixel(sx, sy, sf::Color(0, 0, 0, 0));

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

				spriteRenderTexture->display();
				sf::Texture marioTexture = spriteRenderTexture->getTexture();
				sf::Sprite spriteToDisplay;
				spriteToDisplay.setTexture(marioTexture);

				sf::Image image = marioTexture.copyToImage();
				image.saveToFile("res/sprites/Map/" + m_name + "-" + std::to_string(nSprite) + ".png");

				nSprite++;
				continue;
			}
			else
			{
				bool foundPixel = false;
				for (size_t i = 0; i < 8; i++)
				{
					if (y + i < sheetSize.y && imageMapSheet.getPixel(x, y + i).a != 0)
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
	}

	loadSprites();
	loadAnimation();

	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(stagePosition.x, stagePosition.y*2);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	createShape(stageSize, std::vector<b2Vec2>{
							b2Vec2(0.0f, 0.0f), b2Vec2(10.0f, 0.0f), b2Vec2(10.0f, 10.0f)});
}

void Map::update(float deltaTime)
{
	animations[m_name].update(deltaTime);
	textureToDraw = animations[m_name].getTexture();
}

void Map::draw(Renderer& renderer, sf::Vector2f position, sf::Vector2f size)
{
	auto textureSize = textureToDraw.getSize();
	float xRatio = 0.02f;
	float yRatio = 0.07f;

	stagePosition = sf::Vector2f(position.x, position.y + 4);
	stageSize = sf::Vector2f(textureSize.x * xRatio, textureSize.y * yRatio);
	if (stageSize != previousStageSize)
	{
		auto fixtures = body->GetFixtureList();
		while (fixtures != nullptr)
		{
			auto next = fixtures->GetNext();
			body->DestroyFixture(fixtures);
			fixtures = next;
		}
		auto vertices = getFixtureSize(textureToDraw);
		for (auto &point : vertices)
		{
			std::cout << point.x << ";" << point.y << std::endl;
			point = b2Vec2(point.x * xRatio, point.y * yRatio);
		}
		std::cout << vertices.size() << std::endl;
		createShape(sf::Vector2f(textureSize.x * xRatio, textureSize.y * yRatio), vertices);
		previousStageSize = stageSize;
	}
	body->SetTransform(b2Vec2(stagePosition.x - stageSize.x / 2, stagePosition.y - stagePosition.y * 1.5), body->GetAngle());
	renderer.draw(textureToDraw, stagePosition, stageSize);
}

void Map::onBeginContact(b2Fixture* self, b2Fixture* other)
{
}

void Map::onEndContact(b2Fixture* self, b2Fixture* other)
{
}

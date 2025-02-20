#include "Game.h"
#include "Resources.h"
#include "Physics.h"
#include "Map.h"
#include "Object.h"
#include "Menu.h"
#include <filesystem>
#include <algorithm>
#include "Character.h"

ENetAddress address;
ENetHost* server;
ENetHost* client;
ENetEvent enetEvent;
ENetPeer* peer;

Menu menu(window);
Map map("Final Destination");
Camera camera(25.0f);
Character* character = new Character("Mario", true);

std::map<Character*, bool> characters{};

std::map<ENetPeer*, Character*> playersCharacter{};
std::map<ENetPeer*, bool> playersAvailability{};

bool paused = false;
bool menuState = true;

sf::Font font{};

sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));

int iPacket = 0;

std::vector<std::string> mapVector;
std::vector<std::string> characterVector;
	
void loadMap(std::string name)
{
	// Vérifier si le dossier existe déjà
	if (!std::filesystem::exists("./res/sprites/Map")) {
		// Créer le dossier
		if (std::filesystem::create_directory("./res/sprites/Map")) {
			std::cout << "Dossier créé avec succès : map" << std::endl;
		}
		else {
			std::cerr << "Erreur lors de la création du dossier." << std::endl;
		}
	}
	else {
		std::cout << "Le dossier existe déjà." << std::endl;
	}
	std::vector<sf::RenderTexture*> renderList;
	sf::Texture mapSheet = Resources::textures["Sheet/" + name + ".png"];
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
				image.saveToFile("res/sprites/Map/" + name + "-" + std::to_string(nSprite) + ".png");

				std::cout << name + "-" + std::to_string(nSprite) + ".png" << std::endl;
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
}

void loadCharacter(std::string name)
{
	// Vérifier si le dossier existe déjà
	if (!std::filesystem::exists("./res/sprites/" + name)) {
		// Créer le dossier
		if (std::filesystem::create_directory("./res/sprites/" + name)) {
			std::cout << "Dossier créé avec succès : " << name << std::endl;
		}
		else {
			std::cerr << "Erreur lors de la création du dossier." << std::endl;
		}
	}
	else {
		std::cout << "Le dossier existe déjà." << std::endl;
	}

	std::vector<std::string> animationNames = { "stand", "jump", "running", "attacks", "upaerial", "downtilt",
										"smash", "tilt", "aerial", "damage", "guarding", "win", "loose", "uptilt" };

	std::vector<sf::RenderTexture*> renderList;
	sf::Texture marioSheet = Resources::textures["Sheet/" + name + ".png"];
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
					image.saveToFile("res/sprites/" + name + "/" + animName.back() + "-" + std::to_string(i) + ".png");

				}
				std::cout << renderList.size() << " : " << animName.back() << std::endl;
				renderList.clear();
				animName.pop_back();
			}
		}
	}
}

void restart()
{
	Physics::init();

	paused = false;

	menu.begin();

	for (auto m : mapVector)
	{
		loadMap(m);
	}
	for (auto c : characterVector)
	{
		loadCharacter(c);
	}

	//std::cout << "Load map : " << std::endl;
	map = Map("Final Destination");
	map.begin();
}


void begin()
{
	for (auto& directory : std::filesystem::directory_iterator("./res/sprites/"))
	{
		if (directory.is_directory())
		{
			std::string directorStr = directory.path().filename().string();
			for (auto& file : std::filesystem::directory_iterator("./res/sprites/" + directory.path().filename().string()))
			{
				if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
				{
					Resources::textures[directory.path().filename().string() + "/" + file.path().filename().string()].loadFromFile(file.path().string());
				}
				if (directorStr.ends_with("Sheet"))
				{
					if(!file.path().filename().string().starts_with("Map-"))
						characterVector.push_back(file.path().stem().filename().string());
					else
						mapVector.push_back(file.path().stem().filename().string());
				}
			}
			std::vector<std::string> vector;
			for (auto m : mapVector)
			{
				if (!directorStr.find(m))
				{
					vector.push_back(m);
				}
			}
			mapVector = vector;
			vector.clear();
			for (auto c : characterVector)
			{
				if (!directorStr.find(c))
				{
					vector.push_back(c);
				}
			}
			characterVector = vector;
		}
	}
	for (auto sprite : Resources::textures)
	{
		std::cout << sprite.first << std::endl;
	}

	for (auto& file : std::filesystem::directory_iterator("./res/audio/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".wav" || file.path().extension() == ".ogg"))
		{
			Resources::sounds[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}
	font.loadFromFile("./res/font.ttf");

	backgroundShape.setFillColor(sf::Color(0, 0, 0, 155));
	backgroundShape.setOrigin(0.5f, 0.5f);

	restart();
}

void update(float deltaTime)
{
	if(!menuState)
	{
		Physics::update(deltaTime);
		map.update(deltaTime);

		for (auto const player : playersCharacter)
		{
			if(player.first == 0)
			{
				player.second->update(deltaTime);
			}	
			else
			{
				player.second->update(deltaTime);
			}
		}
	}
}

void updateUI(float deltaTime, sf::Event event)
{
	if(menuState)
	{
		menu.update(deltaTime, event, camera.getm_viewSize(), camera.getm_position());
	}
}

void render(Renderer& renderer)
{
	if (!menuState)
	{
		map.draw(renderer, camera.getm_position(), camera.getm_viewSize());
		
		for (auto const player : playersCharacter)
		{
			if (player.first == 0)
			{
				player.second->draw(renderer);
			}
			else
			{
				player.second->draw(renderer);
			}
		}

		Physics::DebugDraw(renderer);
	}
}

void renderUI(Renderer& renderer)
{
	if (menuState)
	{
		menu.draw(renderer);
	}
}

void updateServer()
{
	if(server != NULL)
	{
		bool host_service = true;
		Character::CharacterData characterData;
		/* Wait up to 0 milliseconds for an event. */
		while (enet_host_service(server, &enetEvent, 10) > 0 && host_service)
		{
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				if (enetEvent.peer == nullptr)
				{
					std::cerr << "Erreur: peer est NULL lors de la connexion !" << std::endl;
					break;
				}
				printf("A new client connected from %x:%u.\n",
					enetEvent.peer->address.host,
					enetEvent.peer->address.port);
				enet_peer_timeout(enetEvent.peer, 10000, 5000, 50000); // timeout du kick
				// 10000 : limite avant que l'inactivité du client soit condidéré comme suspectf
				// 5000 : temps minimum avant la première vérification du timeout
				// 50000 : temps maximum avant que le client soit déconnecté pour inactivité

				playersAvailability[enetEvent.peer] = false;

				break;

			case ENET_EVENT_TYPE_RECEIVE:
				//std::cout << "serveur : ENET_EVENT_TYPE_RECEIVE" << std::endl;
				playersAvailability[enetEvent.peer] = true;
				memcpy(&characterData, enetEvent.packet->data, sizeof(Character::CharacterData));

				//std::cout << "serveur : packet reçu de " << enetEvent.peer << std::endl;
				// Envoie le packet à tous les clients
				for (auto i = 0; i < server->peerCount; i++)
				{
					if (playersAvailability[&server->peers[i]] && enetEvent.peer != &server->peers[i])
					{
						//std::cout << "enet_peer_send(server->peers)" << std::endl;
						enet_peer_send(&server->peers[i], 0, enetEvent.packet);
					}
				}
				//enet_host_broadcast(server, 0, enetEvent.packet);
				enet_host_flush(server);
				//updateClient();

				/* Clean up the packet now that we're done using it. */
				enet_packet_destroy(enetEvent.packet);
				//host_service = false;

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("A client disconnected from %x:%u.\n",
					enetEvent.peer->address.host,
					enetEvent.peer->address.port);
				break;
			}
		}
	}
}

void updateClient()
{
	if(client != NULL)
	{
		Character::CharacterData characterData;
		while (enet_host_service(client, &enetEvent, 10) > 0)
		{
			//std::cout << "enet_host_service > 0" << std::endl;
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				memcpy(&characterData, enetEvent.packet->data, sizeof(Character::CharacterData));
				//std::cout << "paquet reçu" << std::endl;
				
				if (!playersCharacter.contains(enetEvent.peer))
				{
					std::cout << "nouveau joueur" << std::endl;
					Character* player = new Character(characterData.name, false);
					player->begin();
					playersCharacter[enetEvent.peer] = player;
				}
				else
				{
					/*playersCharacter[enetEvent.peer]->position = characterData.position;
					playersCharacter[enetEvent.peer]->size = characterData.size;
					playersCharacter[enetEvent.peer]->textureToDraw = characterData.texture;*/

					std::vector<bool> receivedActionsState{ characterData.attacks, characterData.down,
															characterData.guarding,characterData.left,
															characterData.right, characterData.smash,
															characterData.tilt, characterData.up };
					

					playersCharacter[enetEvent.peer]->setm_actionsState(receivedActionsState);
					playersCharacter[enetEvent.peer]->textureToDraw = characterData.texture;
					playersCharacter[enetEvent.peer]->position = characterData.position;
				}

				/*playersCharacter[enetEvent.peer] = characterData.player;
				std::cout << "playersCharacter[enetEvent.peer] mis à jour" << std::endl;*/

				printf("Packet n%d : %s = right : %d\n", iPacket, characterData.name, (int)characterData.right);
				iPacket++;

				enet_packet_destroy(enetEvent.packet);
				break;
			}
		}
	}
}

void initializeServer()
{
	if (enet_initialize() != 0)
	{
		std::cerr << "An error occured while initializing Enet." << std::endl;
	}

	address.host = ENET_HOST_ANY;
	address.port = 1234;

	server = enet_host_create(&address /* the address to bind the server host to */,
								32      /* allow up to 32 clients and/or outgoing connections */,
								2      /* allow up to 2 channels to be used, 0 and 1 */,
								0      /* assume any amount of incoming bandwidth */,
								0      /* assume any amount of outgoing bandwidth */);
	if (server) 
	{
		std::cout << "Serveur lancé avec succès sur le port " << address.port << std::endl;
	}
	else
	{
		std::cerr << "An error occured while trying to create an ENet server host." << std::endl;
	}

	std::cout << "Server host : " << address.host << std::endl;
	std::cout << "Server port : " << address.port << std::endl;

	joinServer("127.0.0.1:" + std::to_string(address.port));
}

void joinServer(std::string hostPort)
{
	std::cout << "joinServer" << std::endl;
	std::string hostStr;
	std::string portStr;
	int port;

	std::cout << "début de la boucle" << std::endl;
	std::cout << hostPort << std::endl;
	for (auto i = 0; i < hostPort.size(); i++)
	{
		if (hostPort[i] == ':')
		{
			for (auto j = 0; j < i; j++)
			{
				hostStr.push_back(hostPort[j]);
			}
			for (auto j = i + 1; j < hostPort.size(); j++)
			{
				portStr.push_back(hostPort[j]);
			}
		}
	}
	std::cout << "création var port : " << portStr << std::endl;
	port = std::stoi(portStr);
	std::cout << "création var host : " << hostStr << std::endl;
	const char* host = hostStr.c_str();

	std::cout << "Création du client" << std::endl;
	client = enet_host_create(NULL /* create a client host */,
								1 /* only allow 1 outgoing connection */,
								2 /* allow up 2 channels to be used, 0 and 1 */,
								0 /* assume any amount of incoming bandwidth */,
								0 /* assume any amount of outgoing bandwidth */);
	if (client == NULL)
	{
		std::cerr << "An error occured while trying to create an ENet client host." << std::endl;
	}

	std::cout << "Connexion au serveur" << std::endl;
	if (enet_address_set_host(&address, host) != 0)
	{
		std::cerr << "erreur lors du set_host" << std::endl;
	}
	address.port = port;

	std::cout << "initialisation de la connexion" << std::endl;
	peer = enet_host_connect(client, &address, 2, 0);
	enet_host_flush(client);

	if (peer == NULL)
	{
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
	}

	/* Wait up to 5 seconds for the connection attempt to succeed. */
	if (enet_host_service(client, &enetEvent, 5000) > 0 &&
		enetEvent.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connexion Succeeded" << std::endl;
		std::cout << "Server host : " << address.host << std::endl;
		std::cout << "Server port : " << address.port << std::endl;
	}
	else
	{
		/* Either the 5 seconds are up or a disconnect event was */
		/* received. Reset the peer in the event the 5 seconds   */
		/* had run out without any significant event.            */
		//enet_peer_reset(peer);

		std::cout << "Connexion Failed" << std::endl;
		std::cout << "Server host : " << address.host << std::endl;
		std::cout << "Server port : " << address.port << std::endl;
	}
}

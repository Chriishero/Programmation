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
std::vector<Character*> characters{};

std::map<ENetPeer*, Character*> playersCharacter{};
std::map<ENetPeer*, bool> playersAvailability{};

bool paused = false;
bool menuState = true;

sf::Font font{};

sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));

int iPacket = 0;
	
void restart()
{
	Physics::init();

	paused = false;

	menu.begin();

	std::cout << "Load map : " << std::endl;
	map = Map("Final Destination");
	map.begin();
}


void begin()
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

		for (auto const chara : characters)
		{
			chara->update(deltaTime);
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
		
		for (auto const chara : characters)
		{
			chara->draw(renderer);
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
		Character::CharacterData characterData;
		/* Wait up to 0 milliseconds for an event. */
		while (enet_host_service(server, &enetEvent, 30) > 0)
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
				playersAvailability[enetEvent.peer] = true;
				memcpy(&characterData, enetEvent.packet->data, sizeof(Character::CharacterData));

				// Envoie le packet à tous les clients

				for (auto i = 0; i < server->peerCount; i++)
				{
					if (playersAvailability[&server->peers[i]])
					{
						enet_peer_send(&server->peers[i], 0, enetEvent.packet);;
					}
				}
				//enet_host_broadcast(server, 0, enetEvent.packet);
				enet_host_flush(server);

				/* Clean up the packet now that we're done using it. */
				enet_packet_destroy(enetEvent.packet);

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
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				memcpy(&characterData, enetEvent.packet->data, sizeof(Character::CharacterData));

				/*if (!playersCharacter.contains(enetEvent.peer))
				{
					std::cout << "nouveau personnage" << std::endl;
					Character* player = new Character(characterData.name, false);
					player->begin();
					playersCharacter[enetEvent.peer] = player;
				}
				else
				{
					playersCharacter[enetEvent.peer]->position = characterData.position;
					playersCharacter[enetEvent.peer]->size = characterData.size;
					playersCharacter[enetEvent.peer]->textureToDraw = characterData.texture;
				}*/

				printf("Packet n%d : %s : (%f;%f)\n", iPacket, characterData.name, characterData.position.x, characterData.position.y);
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

	playersCharacter[peer] = character;

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

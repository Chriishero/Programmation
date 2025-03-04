#include <SFML/Graphics.hpp>
#include <enet/enet.h>
#include "Renderer.h"
#include "Camera.h"
#include "Character.h"
#include <iostream>
#include <string>

extern Camera camera;
extern Character* character;
extern Map* map;
extern std::map<Character*, bool> characters;
extern std::map<ENetPeer*, Character*> playersCharacter;
extern bool paused;
extern bool menuState;
extern sf::Font font;
extern sf::RenderWindow window;
extern bool gameOver;
extern int resultPlace;
extern bool mapState;
extern std::string mapStr;

extern ENetAddress address;
extern ENetHost* server;
extern ENetHost* client;
extern ENetEvent enetEvent;
extern ENetPeer* peer;

void loadMap(std::string name);
void loadCharacter(std::string name);
void restart();
void begin();
void update(float deltaTime);
void updateUI(float deltaTime, sf::Event event);
void render(Renderer& renderer);
void renderUI(Renderer& renderer);
void updateServer();
void updateClient();
void initializeServer();
bool joinServer(std::string hostPort);
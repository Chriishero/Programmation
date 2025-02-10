#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Camera.h"
#include <iostream>

extern Camera camera;
extern bool paused;
extern bool menuState;
extern sf::RenderWindow window;

void restart();
void begin();
void update(float deltaTime);
void updateUI(float deltaTime, sf::Event event);
void render(Renderer& renderer);
void renderUI(Renderer& renderer);


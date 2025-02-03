#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Camera.h"
#include <iostream>

extern Camera camera;
extern bool paused;
extern bool title;

void restart();
void begin();
void update(float deltaTime);
void render(Renderer& renderer);
void renderUI(Renderer& renderer);

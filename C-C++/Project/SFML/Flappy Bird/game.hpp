#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#include "camera.hpp"
#include <iostream>

extern Camera camera;
extern bool paused;
extern bool title;

void restart();
void begin();
void update(float deltaTime);
void render(Renderer& renderer);
void renderUI(Renderer& renderer);

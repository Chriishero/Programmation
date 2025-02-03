#pragma once
#ifndef __MAIN__
#define __MAIN__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "input.h"

const int WIN_WIDTH = 1080;
const int WIN_HEIGHT = 680;

// Prototypes fonctions
void checkButton();
void deplacementEnnemie(sf::RectangleShape& ennemie);
void deplacementBall(sf::CircleShape& item, sf::RectangleShape& entity, sf::RectangleShape& ennemie);
void loadFont();
void setScore(sf::Text& txt, sf::String str);
void setInitialState(sf::CircleShape& item, sf::RectangleShape& entity, sf::RectangleShape& ennemie);

// Prototypes structures
struct Direction { bool right, left, up, down; };

#endif // !"__MAIN__"

#pragma once
#ifndef __INPUT__
#define __INPUT__

#include <SFML/Graphics.hpp>

class Input
{
	struct Button { bool up, down, left, right, escape; };
public:
	Input();

	Button getButton() const;
	void inputHandler(sf::Event event, sf::RenderWindow& window);

private:
	Button button;

};

#endif // !__INPUT__

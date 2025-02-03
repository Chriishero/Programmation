#include "main.h"

// Var global
sf::RenderWindow window;
sf::Font font;
sf::Text txt;
Input input;

float xSize = 40;
float ySize = WIN_HEIGHT / 3;

float entity_xPos = 0;
float entity_yPos = WIN_HEIGHT / 3;
float entity_speed = 60;
int entityPoint = 0;

float ennemie_xPos = WIN_WIDTH - xSize;
float ennemie_yPos = WIN_HEIGHT / 3;
bool ennemie_UpDown = false;
float ennemie_speed = 5;
int ennemiePoint;

float ball_speed = 10;
float ball_xPos = WIN_WIDTH / 2;
float ball_yPos = WIN_HEIGHT / 2;

float left_border = 0;
float right_border = WIN_WIDTH;
float up_border = 0;
float down_border = WIN_HEIGHT;

Direction direction;

int main()
{
	sf::ContextSettings options;
	options.antialiasingLevel = 8;
	window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Pong Game", sf::Style::Default, options);
	window.setVerticalSyncEnabled(true);

	// Entité
	sf::RectangleShape entity(sf::Vector2f(xSize, ySize));
	entity.setPosition(entity_xPos, entity_yPos);

	sf::RectangleShape ennemie(sf::Vector2f(xSize, ySize));
	ennemie.setPosition(ennemie_xPos, ennemie_yPos);

	// Balle 
	sf::CircleShape ball(25);
	ball.setPosition(ball_xPos, ball_yPos);

	// Direction initial 
	direction.right = direction.up = direction.down = false;
	direction.left = true;

	// Font
	loadFont();
	setScore(txt, std::to_string(entityPoint) + " | " + std::to_string(ennemiePoint));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			input.inputHandler(event, window);
			checkButton();
			entity.setPosition(entity_xPos, entity_yPos);
			ennemie.setPosition(ennemie_xPos, ennemie_yPos);
		}
		deplacementBall(ball, entity, ennemie);
		deplacementEnnemie(ennemie);

		window.clear(sf::Color::Black);

		window.draw(entity);
		window.draw(ennemie);
		window.draw(ball);
		window.draw(txt);

		window.display();
	}

	return 0;
}

void checkButton()
{
	auto buttons = input.getButton();
	if (buttons.escape == true)
	{
		window.close();
	}
	if (buttons.up == true)
	{
		entity_yPos -= entity_speed;
		if (entity_yPos < 0)
		{
			entity_yPos = 0;
		}
	}
	if (buttons.down == true)
	{
		entity_yPos += entity_speed;
		if (entity_yPos > WIN_HEIGHT - ySize)
		{
			entity_yPos = WIN_HEIGHT - ySize;
		}
	}
	if (buttons.left == true)
	{
		ennemie_yPos -= entity_speed;
		if (ennemie_yPos < 0)
		{
			ennemie_yPos = 0;
		}
	}
	if (buttons.right == true)
	{
		ennemie_yPos += entity_speed;
		if (ennemie_yPos > WIN_HEIGHT - ySize)
		{
			ennemie_yPos = WIN_HEIGHT - ySize;
		}
	}
}

void deplacementEnnemie(sf::RectangleShape& ennemie)
{
	/*if (ennemie_UpDown == false)
	{
		ennemie_yPos += ennemie_speed;
		if (ennemie_yPos > WIN_HEIGHT - ySize)
		{
			ennemie_yPos = WIN_HEIGHT - ySize;
			ennemie_UpDown = true;
		}
	}
	else if (ennemie_UpDown == true)
	{
		ennemie_yPos -= ennemie_speed;
		if (ennemie_yPos < 0)
		{
			ennemie_yPos = 0;
			ennemie_UpDown = false;
		}
	}*/
	ennemie_yPos = ball_yPos;
	ennemie.setPosition(ennemie_xPos, ennemie_yPos);
}

void deplacementBall(sf::CircleShape& item, sf::RectangleShape& entity, sf::RectangleShape& ennemie)
{
	if (direction.right == true)
	{
		ball_xPos = item.getPosition().x + ball_speed;
		if (item.getPosition().y >= ennemie.getPosition().y && item.getPosition().y <= ennemie.getPosition().y + ySize)
		{
			right_border = WIN_WIDTH-xSize*2;
			std::cout << right_border << std::endl;
		}
		else {
			right_border = WIN_WIDTH;
		}
	}
	else if (direction.left == true)
	{
		ball_xPos = item.getPosition().x - ball_speed;
		if (item.getPosition().y >= entity.getPosition().y && item.getPosition().y <= entity.getPosition().y + ySize)
		{
			left_border = xSize;
			std::cout << left_border << std::endl;
		}
		else {
			left_border = 0;
		}
	}
	if(direction.up == true)
	{
		ball_yPos = item.getPosition().y - ball_speed;
	}
	else if (direction.down == true)
	{
		ball_yPos = item.getPosition().y + ball_speed;
	}
	else {
		ball_yPos = item.getPosition().y;
	}

	if (ball_xPos > right_border)
	{
		ball_xPos = right_border;
		direction.right = false;
		direction.left = true;
		if (item.getPosition().y >= ennemie.getPosition().y &&
			item.getPosition().y <= ennemie.getPosition().y + ySize / 3)
		{
			direction.down = true;
			direction.up = false;
		}
		if (item.getPosition().y >= ennemie.getPosition().y + ySize / 3 &&
			item.getPosition().y <= ennemie.getPosition().y + ySize / 3 * 2)
		{
			direction.down = false;
			direction.up = false;
		}
		if (item.getPosition().y >= ennemie.getPosition().y + ySize / 3 * 2 &&
			item.getPosition().y <= ennemie.getPosition().y + ySize)
		{
			direction.down = false;
			direction.up = true;
		}
		if (right_border == WIN_WIDTH)
		{
			entityPoint += 1;
			setScore(txt, std::to_string(entityPoint) + " | " + std::to_string(ennemiePoint));

			direction.right = direction.up = direction.down = false;
			direction.left = true;

			setInitialState(item, entity, ennemie);
			sf::sleep(sf::seconds(1));
		}
	}
	else if (ball_xPos < left_border)
	{
		ball_xPos = left_border;
		direction.left = false;
		direction.right = true;

		if (item.getPosition().y >= entity.getPosition().y &&
			item.getPosition().y <= entity.getPosition().y + ySize / 3)
		{
			direction.down = true;
			direction.up = false;
		}
		if (item.getPosition().y >= entity.getPosition().y + ySize/3 &&
			item.getPosition().y <= entity.getPosition().y + ySize/3*2)
		{
			direction.down = false;
			direction.up = false;
		}
		if (item.getPosition().y >= entity.getPosition().y + ySize/3*2 &&
			item.getPosition().y <= entity.getPosition().y + ySize)
		{
			direction.down = false;
			direction.up = true;
		}
		if (left_border == 0)
		{
			ennemiePoint += 1;
			setScore(txt, std::to_string(entityPoint) + " | " + std::to_string(ennemiePoint));

			direction.left = direction.up = direction.down = false;
			direction.right = true;

			setInitialState(item, entity, ennemie);
			sf::sleep(sf::seconds(1));
		}
	}
	if (ball_yPos > down_border)
	{
		ball_yPos = down_border;
		direction.down = false;
		direction.up = true;
	}
	else if (ball_yPos < up_border)
	{
		ball_yPos = up_border;
		direction.up = false;
		direction.down = true;
	}

	item.setPosition(ball_xPos, ball_yPos);
}

void loadFont()
{
	if (!font.loadFromFile("res/Poppins,Source_Code_Pro/Poppins/Poppins-Regular.ttf"))
	{
		std::cout << "La police d'écriture n'a pas été chargé." << std::endl;
	}
}

void setScore(sf::Text& txt, sf::String str)
{
	txt.setFont(font);
	txt.setString(str);
	txt.setCharacterSize(26);
	txt.setPosition(WIN_WIDTH / 2, 0);
}

void setInitialState(sf::CircleShape& item, sf::RectangleShape& entity, sf::RectangleShape& ennemie)
{
	ball_xPos = WIN_WIDTH / 2;
	ball_yPos = WIN_HEIGHT / 2;

	entity_xPos = 0;
	entity_yPos = WIN_HEIGHT / 3;

	ennemie_xPos = WIN_WIDTH - xSize;
	ennemie_yPos = WIN_HEIGHT / 3;

	entity.setPosition(entity_xPos, entity_yPos);
	ennemie.setPosition(ennemie_xPos, ennemie_yPos);
}
#pragma once

#include <SFML/Graphics.hpp>
#include "Pillar.h"
#include "Brain.h"

class Bird
{

public:
	Bird();
	~Bird();

	void init(sf::Color birdColour);

	//the game loop method
	void update(Pillar pillar);

	//draw the game elements
	void draw(sf::RenderWindow& game_window, Pillar pillar);

	bool think(int x, int upperH, int lowerY);

	void reset();
	bool jump = false;

	sf::RectangleShape rectangle;

	sf::Vertex line1[2] =
	{
		sf::Vertex(sf::Vector2f(10.f, 10.f)),
		sf::Vertex(sf::Vector2f(150.f, 150.f))
	};	
	sf::Vertex line2[2] =
	{
		sf::Vertex(sf::Vector2f(10.f, 10.f)),
		sf::Vertex(sf::Vector2f(150.f, 150.f))
	};

	int x;
	int y;
	int w;
	int h;
	sf::Color colour;

	int fitness;
	float score = 0.0;

	bool alive;

	Brain brain;

};

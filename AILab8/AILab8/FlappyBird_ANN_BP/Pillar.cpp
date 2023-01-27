#include "Pillar.h"
#include "Game.h"
#include <iostream>

using namespace std;

/// <summary>
/// Default constructor
/// 
/// 
/// </summary>
Pillar::Pillar()
{
}

/// <summary>
/// Default destructor
/// 
/// 
/// </summary>
Pillar::~Pillar()
{

}

void Pillar::init(int start)
{
	gap = 100;	// Betwen top and bottom pillar.

	pillarWidth = 50;
	x = start;
	upperY = 0;
	upperH = rand() % (Game::height - gap - 20);
	if (upperH < 0)
		upperH = 20; //Minimum pillar height of 20.

	lowerY = rand() % (Game::height - gap - upperH - 20) + upperH + gap + 20;
	lowerH = Game::height - lowerY;

	colour = sf::Color::Cyan;

	upperRectangle.setPosition(x, 0);
	upperRectangle.setSize(sf::Vector2f(pillarWidth, upperH));
	upperRectangle.setFillColor(colour);
	
	lowerRectangle.setPosition(x, lowerY);
	lowerRectangle.setSize(sf::Vector2f(pillarWidth, lowerH));
	lowerRectangle.setFillColor(colour);

//	std::cout << "x: " << x << " upperY: " << upperY << " upperH: " << upperH << " lowerY: " << lowerY << " lowerH: " << lowerH << std::endl;

}


void Pillar::update(float dt, Pillar pillarSet[])
{
	x += -3;	// Pillars just keep moving left
	if (x < 0)
		reset(pillarSet);

	upperRectangle.setFillColor(colour);
	upperRectangle.setPosition(x, 0);
	upperRectangle.setSize(sf::Vector2f(pillarWidth, upperH));
	lowerRectangle.setFillColor(colour);
	lowerRectangle.setPosition(x, lowerY);
	lowerRectangle.setSize(sf::Vector2f(pillarWidth, lowerH));

}

void Pillar::reset(Pillar pillarSet[])
{
	// Find where to position the pillar on the right hand side 
	// since it has dropped off the screen on the left.
	int index = 0;
	for (int i = 0; i < Game::pillarCount; i++)
	{
		if (pillarSet[i].x > pillarSet[index].x)
			index = i;
	}

	x = pillarSet[index].x + Game::pillarGap;
	upperH = rand() % (Game::height - gap - 20);
	if (upperH < 0)
		upperH = 20;
	lowerY = rand() % (Game::height - gap - upperH - 20) + upperH + gap + 20;
	lowerH = Game::height - lowerY;
	if (lowerH < 0)
		lowerH = 20;

//	std::cout << "x: " << x << " upperY: " << upperY << " upperH: " << upperH << " lowerY: " << lowerY << " lowerH: " << lowerH << std::endl;
//	std::cout << "..." << std::endl;

}

/// <summary>
/// Draw the game entities
/// 
/// 
/// </summary>
void Pillar::draw(sf::RenderWindow& game_window)
{
	game_window.draw(upperRectangle);
	game_window.draw(lowerRectangle);
}


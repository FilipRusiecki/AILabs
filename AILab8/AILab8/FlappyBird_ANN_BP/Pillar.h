#pragma once

#include <SFML/Graphics.hpp>

// Pillar or Obstacle

class Pillar
{

public:
	//Default constructor
	Pillar();
	//Default destructor
	~Pillar();
	//function ran when the game starts
	void init(int start);
	//the game loop method
	void loop();
	//update game logic
	void update(float dt, Pillar pillarSet[]);
	//draw the game elements
	void draw(sf::RenderWindow& game_window);
	void reset(Pillar pillarSet[]);

//private:
	int gap;
	int pillarWidth;
	int start;
	int x;
	int upperY;
	int upperH;
	int w;
	int lowerY;
	int lowerH;
	sf::Color colour;
	sf::RectangleShape upperRectangle;
	sf::RectangleShape lowerRectangle;

};


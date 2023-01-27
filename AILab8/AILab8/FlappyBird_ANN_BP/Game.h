#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include "Pillar.h"
#include "Bird.h"
#include "Population.h"
#include <fstream>

///
/// Game class is the main loop of the game that updates and draws the game
///
class Game
{

public:
	static const int width = 1500;
	static const int height = 800;
	static const int pillarGap = 600;	// The gap between pillars
	static const int pillarCount = 5;

	static const bool player = true;	// True if human wants to play. Don't forget to set birdCount=1 below.
	static const bool ai = false;		// True if we are loading a neural network and the AI plays. Don't forget to set birdCount=1 below.

	static const int birdCount = 1;		// Set to 1 if we are in player mode.
										// If in AI mode and you set it to more than one 
										// then all birds will have the same brain type and will start in different vertical positions.

	bool capture = false;
	bool render = true;
	std::ofstream myTrainingfile;
	std::ifstream myWeightsFile;

	sf::Text text;
	int currentSpeed = 0;
	int bestSoFar = 0;

	//Default constructor
	Game();
	//Default destructor
	~Game();
	//function ran when the game starts
	void init();
	//Load the trained neural network from file
	void loadTFBrain(int bird);
	//the game loop method
	void loop();
	//update game logic
	void update(float dt);
	//draw the game elements
	void draw();
	void resetPillars();
	sf::RenderWindow m_window;



private:
	sf::Vector2f m_mousePos;
	sf::Font font;

	sf::VertexArray lines;

	bool m_exitGame; // control exiting game
	bool showBirdStats = true;


	Pillar pillarSet[pillarCount];
	int index = 0; //The pillar the bird is approaching.

	Population population;


};


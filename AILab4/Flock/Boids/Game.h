#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include "Boid.h"
#include "Pvector.h"
#include "Flock.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <string>
using namespace std;

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

	int window_height;
	int window_width;

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window; // main SFML window
	//Gets the resolution, size, and bits per pixel for the screen of the PC that is running this program.
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Font m_font;
	sf::Text m_actionMessage; // text used for message on screen

	bool m_exitGame; // control exiting game

	float boidsSize = 3;
	float enemySize = 10;
	string action = "flock";
	bool close = false;

	//Create flock, vector of shapes, and initialize boids
	Flock flock;
	vector<sf::CircleShape> shapes;

};

#endif // !GAME_HPP


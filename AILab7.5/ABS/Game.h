#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Droid.h"
#include "HealthPill.h"
#include <SFML/Graphics.hpp>

//using namespace std;

class Game
{
public:

	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);
	
/// <summary>
/// This is the grid.
/// It will also contain a list of all the nodes and what type of nodes they are.
/// </summary>
	Grid gridWorld = Grid(30);

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void updateDroids();
	void render();
	void setupFontAndText();
	void setupDroids();
	void setupGrid();
	void drawGrid(sf::RenderWindow& t_window);
	void drawDroids(sf::RenderWindow& t_window);
	void drawHealthPills(sf::RenderWindow& t_window);
	void initGridObjects();

	sf::RenderWindow m_window; // main SFML window
//	unsigned int worldWidth = (unsigned)2000;
//	unsigned int worldHeight = (unsigned)1800;
	unsigned int worldWidth = (unsigned)1000;
	unsigned int worldHeight = (unsigned)900;
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo

	bool m_exitGame; // control exiting game
	int goalX;
	int goalY;
	bool goalSet = false;
	std::vector<Droid*> m_droids;
	std::vector<HealthPill*> m_healthPills;
};

#endif // !GAME_H


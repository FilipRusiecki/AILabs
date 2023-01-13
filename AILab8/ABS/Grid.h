#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
//#include "Droid.h"
#include "Node.h"
//#include "HealthPill.h"

class Droid;	// Was getting issues with circular headers so had to forward reference instead.
class HealthPill;

//using namespace std;

/// <summary>
/// This is the grid world for the game.
/// 
/// It is used to create the grid and all of its nodes. It assigns nodes their positions, types.
/// </summary>
class Grid
{
public:
	/// <summary>
	/// This is the Grid's Constructor.
	/// 
	/// This intialises the Grid when created.
	/// </summary>
	Grid(int size);

	/// <summary>
	/// This is the Grid's Decontructor.
	/// 
	/// This is used to destroy any unused memory.
	/// </summary>
	~Grid();

	/// <summary>
	/// This sets up the Grid.
	/// 
	/// This is called and sets up the grid of nodes and what types of nodes they are.
	/// </summary>
	void setupGrid(int size);

	/// <summary>
	/// This is used to draw the Grid.
	/// 
	/// This draws all the nodes on the Grid.
	/// </summary>
	/// <param name="t_window">This is a reference to the window in the game class.</param>
	void draw(sf::RenderWindow& t_window);

	/// <summary>
	/// This gets the length of a vector.
	/// 
	/// This gets the magnitude of a vector and returns it.
	/// </summary>
	/// <param name="t_vect">This is the vector whose magnitude we want.</param>
	/// <returns>This is the length value</returns>
	float length(sf::Vector2f t_vect);

	sf::Vector2f getGridLocation(int x, int y);
	int getGridCellX(sf::Vector2i location);
	int getGridCellY(sf::Vector2i location);

	Node **nodes;	//Design a variable sized grid which will be driven by a gridSize parameter.
	int gridSize;	//Store the Gris size for ease of access later.
	sf::Vector2f startPos = sf::Vector2f(50.0f, 50.0f);
	std::vector<Droid*> m_gridDroids;	//We will need access to all the Droids on the Grid when we are executing certain behaviours.
	std::vector<HealthPill*> m_gridHealthPills;	//We will need access to all the HealthPills on the Grid when we are executing certain behaviours.

};
#endif


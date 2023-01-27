#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>

/// <summary>
/// This is the Node Class.
/// 
/// These are all the node spaces that make up the Grid.
/// </summary>
class Node
{
private:
	/// <summary>
	///This is the nodes position.
	/// </summary>
	sf::Vector2f m_position;
	/// <summary>
	///This is to check if there is a piece on the node.
	/// </summary>
	bool m_containsPiece = false;

public:
	/// <summary>
	/// This is the nodes Contructor.
	/// </summary>
	Node();

	/// <summary>
	/// This is the nodes Decontructor.
	/// </summary>
	~Node();

	/// <summary>
	/// This sets the nodes position.
	/// 
	/// It takes in a vector and sets the circles position to that vector.
	/// </summary>
	/// <param name="t_pos">This is the vector we want the circle to be at.</param>
	void setPos(sf::Vector2f t_pos);

	/// <summary>
	/// This gets the node's current position.
	/// 
	/// This returns a vector2f of the current position.
	/// </summary>
	/// <returns>This is the position of the node.</returns>
	sf::Vector2f getPos();

	/// <summary>
	/// This draws the node.
	/// 
	/// Using a reference to window in the class Game we draw the grid square which represents a node.
	/// </summary>
	/// <param name="t_window">This needs a reference to the Game variable window.</param>
	void draw(sf::RenderWindow &t_window);

	/// <summary>
	/// This sets the nodes colour.
	/// 
	/// This sets the colour of m_circle. We use this to visually distinguise between the different types of nodes.
	/// </summary>
	/// <param name="t_c">We need a type of colour to set the grid square to.</param>
	void setColor(sf::Color t_c);

	/// <summary>
	///This is the nodes visual representation.
	/// </summary>
	sf::RectangleShape m_rectangle;

	const float s_radius = 20;	// Sets the size of each grid square.

};
#endif

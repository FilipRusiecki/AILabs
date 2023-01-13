#include "Node.h"

Node::Node()
{
	m_rectangle.setFillColor(sf::Color::Green);
//	m_rectangle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));		// Cool multi colour grid.
	m_rectangle.setOutlineThickness(-1.0);
	m_rectangle.setOutlineColor(sf::Color::Black);
	m_rectangle.setSize(sf::Vector2f(s_radius, s_radius));
	m_rectangle.setOrigin(0, 0);

}

Node::~Node()
{
}

void Node::setPos(sf::Vector2f t_pos)
{
	m_position = t_pos;
	m_rectangle.setPosition(m_position);
}

sf::Vector2f Node::getPos()
{
	return m_position;
}

void Node::draw(sf::RenderWindow &t_window)
{
	t_window.draw(m_rectangle);
}

void Node::setColor(sf::Color t_c)
{
	m_rectangle.setFillColor(t_c);
}


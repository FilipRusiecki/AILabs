#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
class Arrive
{
public:
	
	sf::Texture m_arriveTexture;			// texture used for arrive
	sf::Sprite m_arriveSprite;				// sprite used for arrive
	Arrive();
	void update(sf::Time& t_deltaTime,Player& t_player);
	void render(sf::RenderWindow& t_window);
	void kinematicWander(sf::Time& t_deltaTime, Player& t_player);
	float angle = 0.0f;
private:
	sf::Vector2f m_direction;
	sf::Vector2f point = { 700.0f,700.0f };
	float m_distance;						 //Distance to travel
	sf::Vector2f m_unitVector;
	float timeToTarget = 0.25f;
	float pi = 3.141592653589793238f;
	sf::Vector2f vel;
	float speed = 2.0f;
	float maxSpeed = 5.0f;
	float maxAngle = 360.0f;
	int randomInt = 0;
	void randomNum();
	void setupSprites();
};



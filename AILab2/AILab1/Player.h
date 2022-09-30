#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{

public:
	sf::Texture m_playerTexture; // texture used for player
	sf::Sprite m_playerSprite; // sprite used for player
	sf::VertexArray playerLine{ sf::Lines };
	sf::Vector2f linePoint;
	sf::CircleShape radius;
	sf::CircleShape radiusSmaller;

	float radiusF= 100.0f;
	float radiusFSmall = 30.0f;

	Player();
	void update(sf::Time& t_deltaTime);
	void reder(sf::RenderWindow& t_window);
	bool tracerAlive = false;

private:
	int playerOffset = 16;
	float angleInRads=0;
	sf::Vector2f vel;
	sf::Vector2f vel2;
	float pi = 3.141592653589793238f;
	float speed = 0.0f;
	float maxSpeedFront = 8.0f;
	float maxSpeedReverse = -8.0f;
	float GetProperRot;
	float rotation = 90;
	bool turnLeft = false;
	bool turnRight = false;
	void setupSprites();
	void playerMovement(sf::Time& t_deltaTime);
	void boundry();
};


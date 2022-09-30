#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Wander
{
public:
	sf::Texture m_wanderTexture; // texture used for alien
	sf::Sprite m_wanderSprite; // sprite used for alien
	sf::CircleShape radius;
	float radiusF = 100.0f;
	void update(sf::Time& t_deltaTime);
	void render(sf::RenderWindow& t_window);
	sf::VertexArray WanderLine{ sf::Lines };
	sf::Vector2f linePoint;
	Wander();
	bool alive = false;
	bool tracerAlive = false;
private:
	sf::Font m_font;
	sf::Text nameTag;
	void kinematicWander(sf::Time& t_deltaTime);
	int Offset = 16;
	float angleInRads = 0;
	float angle = 0.0f;
	float pi = 3.141592653589793238f;
	sf::Vector2f vel;
	float speed = 2.0f;
	float maxSpeed = 5.0f;
	int randomInt = 0;
	void setupSprites();
	void randomNum();
	void boundry();
};


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
class ArriveSlow
{
public:
	sf::Texture m_arrvieTexture; // texture used for alien
	sf::Sprite m_arrvieSprite; // sprite used for alien
	sf::VertexArray LineToPlayer{ sf::Lines };

	void update(sf::Time& t_deltaTime, Player& t_player);
	void render(sf::RenderWindow& t_window);
	ArriveSlow();
	bool alive = false;
	bool tracerAlive = false;
private:
	sf::Font m_font;
	sf::Text nameTag;
	float angle = 0.0f;
	float pi = 3.141592653589793238f;
	float speed = 2.0f;
	float maxSpeed = 2.0f;
	float distance;
	float timeToTarget = 0.25f;
	float GetProperRot;
	float rotation;
	sf::Vector2f distanceVec;
	sf::Vector2f vel;

	void setupSprites();
	void seek(sf::Time& t_deltaTime, Player& t_player);


};


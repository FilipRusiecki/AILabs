#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Player
{

public:
	sf::Texture m_playerTexture; // texture used for player
	sf::Sprite m_playerSprite; // sprite used for player
	Player();
	void update();
	void reder(sf::RenderWindow &t_window);

private:
	float speedX = 10;
	float speedY = 0;

	void setupSprites();
	void playerMovement();

};


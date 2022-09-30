#include "Player.h"
Player::Player()
{
	setupSprites();
}

void Player::setupSprites()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\duck.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading player" << std::endl;
	}	
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setPosition(300.0f, 180.0f);
}

void Player::playerMovement()
{
	m_playerSprite.move(speedX, speedY);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		speedX--; //adding code to get github badge
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		speedX++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		speedY--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		speedY++;
	}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//{
	//	m_playerSprite.move(-10.0f, 0.0f);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//{
	//	m_playerSprite.move(10.0f, 0.0f);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	m_playerSprite.move(0.0f, 10.0f);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//{
	//	m_playerSprite.move(0.0f, -10.0f);
	//}
}

void Player::reder(sf::RenderWindow &t_window)
{
	t_window.draw(m_playerSprite);
}


void Player::update()
{
	playerMovement();
}

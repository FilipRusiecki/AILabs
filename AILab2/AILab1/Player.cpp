#include "Player.h"
Player::Player()
{
	setupSprites();
}

void Player::setupSprites()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\playerShip.png"))
	{
		std::cout << "problem loading player" << std::endl;
	}
	m_playerSprite.setTexture(m_playerTexture);
	
	//college pc
	//m_playerSprite.setPosition(1800.0f, 1800.0f);
	//m_playerSprite.scale(5.0f, 5.0f);

	//my pc 
	m_playerSprite.setPosition(800.0f, 800.0f);
	m_playerSprite.scale(3.0f, 3.0f);
	m_playerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_playerSprite.setOrigin(16.0f, 16.0f);

	radius.setFillColor(sf::Color{ 107, 217, 231, 70 });
	radius.setRadius(radiusF);
	radius.setPosition(m_playerSprite.getPosition().x - radiusF, m_playerSprite.getPosition().y- radiusF);

	radiusSmaller.setFillColor(sf::Color{ 121, 1, 231, 70 });
	radiusSmaller.setRadius(radiusFSmall);
	radiusSmaller.setPosition(m_playerSprite.getPosition().x - radiusFSmall, m_playerSprite.getPosition().y - radiusFSmall);
}

void Player::playerMovement(sf::Time& t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (speed < maxSpeedFront)
		{
			speed += 0.4;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (speed > maxSpeedReverse)
		{
			speed -= 0.4;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		speed = 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		speed = 2.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		speed = 5.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotation = m_playerSprite.getRotation();
		rotation -= 1.8 ;
		if (rotation == 0.0)
		{
			rotation = 359.0;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotation = m_playerSprite.getRotation();
		rotation += 1.8 ;
		
		if (rotation == 360.0)
		{
			rotation = 0;
		}
	}

	vel.x = speed * sin(m_playerSprite.getRotation() * t_deltaTime.asMilliseconds() / 1000);
	vel.y = speed * -cos(m_playerSprite.getRotation() * t_deltaTime.asMilliseconds() / 1000);
	angleInRads = (rotation - 90) * pi / 180;
	linePoint.x = m_playerSprite.getPosition().x + radiusF * cos(angleInRads);
	linePoint.y = m_playerSprite.getPosition().y + radiusF * sin(angleInRads);
	m_playerSprite.move(vel);

	radius.setPosition(m_playerSprite.getPosition().x - radiusF, m_playerSprite.getPosition().y - radiusF);
	radiusSmaller.setPosition(m_playerSprite.getPosition().x - radiusFSmall, m_playerSprite.getPosition().y - radiusFSmall);

	m_playerSprite.setRotation(rotation);
	std::cout << "							player angle: " << rotation << std::endl;

	
}

void Player::boundry()
{

		//moving left off screen
		if (m_playerSprite.getPosition().x > sf::VideoMode::getDesktopMode().width)
		{
			m_playerSprite.setPosition(0 - playerOffset, m_playerSprite.getPosition().y);
		}

		//moving right of screen 
		if (m_playerSprite.getPosition().x < 0 - playerOffset)
		{
			m_playerSprite.setPosition(sf::VideoMode::getDesktopMode().width, m_playerSprite.getPosition().y);
		}

		//moving top of screen 
		if (m_playerSprite.getPosition().y < 0 - playerOffset)
		{
			m_playerSprite.setPosition(m_playerSprite.getPosition().x, sf::VideoMode::getDesktopMode().height);
		}

		//moving bottom of screen 
		if (m_playerSprite.getPosition().y > sf::VideoMode::getDesktopMode().height)
		{
			m_playerSprite.setPosition(m_playerSprite.getPosition().x, 0 - playerOffset);
		}


}



void Player::reder(sf::RenderWindow& t_window)
{
	
	if (tracerAlive == true)
	{
		t_window.draw(playerLine);
		t_window.draw(radius);
		t_window.draw(radiusSmaller);
	}
	t_window.draw(m_playerSprite);

}


void Player::update(sf::Time& t_deltaTime)
{
	playerMovement(t_deltaTime);
	boundry();
	playerLine.clear();
	sf::Vertex begin{m_playerSprite.getPosition(),sf::Color::Cyan };
	playerLine.append(begin);
	sf::Vertex end{linePoint, sf::Color::Cyan };
	playerLine.append(end);
}

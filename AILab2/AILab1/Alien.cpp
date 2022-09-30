#include "Alien.h"


Alien::Alien()
{

	setupSprites();
}

void Alien::update(sf::Time& t_deltaTime)
{
	if (alive == true)
	{
		randomNum();
		boundry();
		kinematicWander(t_deltaTime);
		WanderLine.clear();
		sf::Vertex begin{ m_alienSprite.getPosition(),sf::Color::Yellow };
		WanderLine.append(begin);
		sf::Vertex end{ linePoint, sf::Color::Yellow };
		WanderLine.append(end);
		nameTag.setPosition(m_alienSprite.getPosition());
	}
}

void Alien::render(sf::RenderWindow& t_window)
{
	if (alive == true)
	{
		if (tracerAlive == true)
		{
			t_window.draw(WanderLine);
		}
		t_window.draw(m_alienSprite);
		t_window.draw(nameTag);

		//t_window.draw(radius);
	}
}

void Alien::randomNum()
{						//max min +1 + min
	randomInt = rand() % (10 +10 +1) + -10; //random number between -1 to 1 ;
	std::cout << "Alien rotate offset: " << randomInt << std::endl;
}

void Alien::boundry()
{

	//aline moving left off screen
	if (m_alienSprite.getPosition().x > sf::VideoMode::getDesktopMode().width)
	{
		m_alienSprite.setPosition(0 - Offset, m_alienSprite.getPosition().y);
	}

	//aline moving right of screen 
	if (m_alienSprite.getPosition().x < 0 - Offset)
	{
		m_alienSprite.setPosition(sf::VideoMode::getDesktopMode().width, m_alienSprite.getPosition().y);
	}

	//aline moving top of screen 
	if (m_alienSprite.getPosition().y < 0 - Offset)
	{
		m_alienSprite.setPosition(m_alienSprite.getPosition().x, sf::VideoMode::getDesktopMode().height);
	}

	//aline rmoving bottom of screen 
	if (m_alienSprite.getPosition().y > sf::VideoMode::getDesktopMode().height)
	{
		m_alienSprite.setPosition(m_alienSprite.getPosition().x, 0 - Offset);
	}
}

void Alien::setupSprites()
{
	if (!m_alienTexture.loadFromFile("ASSETS\\IMAGES\\alienShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading npc" << std::endl;
	}
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_alienSprite.setTexture(m_alienTexture);
	//college pc 
	//m_alienSprite.setPosition(500.0f, 500.0f);
	//m_alienSprite.scale(5.0f, 5.0f);
	// my pc
	m_alienSprite.setPosition(500.0f, 500.0f);
	m_alienSprite.scale(3.0f, 3.0f);
	m_alienSprite.rotate(angle);
	m_alienSprite.setOrigin(16.0f, 16.0f);
	m_alienSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	radius.setFillColor(sf::Color{ 107, 217, 231, 70 });
	radius.setRadius(radiusF);
	radius.setPosition(m_alienSprite.getPosition().x - radiusF, m_alienSprite.getPosition().y - radiusF);

	nameTag.setFont(m_font);
	nameTag.setScale(0.5f, 0.5f);
	nameTag.setString("Wander");
}

void Alien::kinematicWander(sf::Time& t_deltaTime)
{

	angle = m_alienSprite.getRotation();
	angle = angle + randomInt;

	if (angle == 360.0)
	{
		angle = 0;
	}
	if (angle == 0.0)
	{
		angle = 359.0;
	}
	angleInRads = (angle - 90) * pi / 180;
	linePoint.x = m_alienSprite.getPosition().x + radiusF * cos(angleInRads);
	linePoint.y = m_alienSprite.getPosition().y + radiusF * sin(angleInRads);

	std::cout << "Alien angle: " << angle << std::endl;
	vel.x = speed * sin(angle * t_deltaTime.asMilliseconds() / 1000);
	vel.y = speed * -cos(angle * t_deltaTime.asMilliseconds() / 1000);
	float squareAns = sqrt((vel.x * vel.x) + (vel.y * vel.y));
	sf::Vector2f normalisedVelocity = vel / squareAns;
	m_alienSprite.move(vel);
	m_alienSprite.setRotation(angle);
	radius.move(vel);
}



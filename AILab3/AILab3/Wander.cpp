#include "Wander.h"


Wander::Wander()
{

	setupSprites();
}

void Wander::update(sf::Time& t_deltaTime)
{
	if (alive == true)
	{
		randomNum();
		boundry();
		kinematicWander(t_deltaTime);
		WanderLine.clear();
		sf::Vertex begin{ m_wanderSprite.getPosition(),sf::Color::Yellow };
		WanderLine.append(begin);
		sf::Vertex end{ linePoint, sf::Color::Yellow };
		WanderLine.append(end);
		nameTag.setPosition(m_wanderSprite.getPosition());
	}
}

void Wander::render(sf::RenderWindow& t_window)
{
	if (alive == true)
	{
		if (tracerAlive == true)
		{
			t_window.draw(WanderLine);
		}
		t_window.draw(m_wanderSprite);
		t_window.draw(nameTag);

		//t_window.draw(radius);
	}
}

void Wander::randomNum()
{						//max min +1 + min
	randomInt = rand() % (10 + 10 + 1) + -10; //random number between -1 to 1 ;
	std::cout << "Alien rotate offset: " << randomInt << std::endl;
}

void Wander::boundry()
{

	//aline moving left off screen
	if (m_wanderSprite.getPosition().x > sf::VideoMode::getDesktopMode().width)
	{
		m_wanderSprite.setPosition(0 - Offset, m_wanderSprite.getPosition().y);
	}

	//aline moving right of screen 
	if (m_wanderSprite.getPosition().x < 0 - Offset)
	{
		m_wanderSprite.setPosition(sf::VideoMode::getDesktopMode().width, m_wanderSprite.getPosition().y);
	}

	//aline moving top of screen 
	if (m_wanderSprite.getPosition().y < 0 - Offset)
	{
		m_wanderSprite.setPosition(m_wanderSprite.getPosition().x, sf::VideoMode::getDesktopMode().height);
	}

	//aline rmoving bottom of screen 
	if (m_wanderSprite.getPosition().y > sf::VideoMode::getDesktopMode().height)
	{
		m_wanderSprite.setPosition(m_wanderSprite.getPosition().x, 0 - Offset);
	}
}

void Wander::setupSprites()
{
	if (!m_wanderTexture.loadFromFile("ASSETS\\IMAGES\\wanderShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading npc" << std::endl;
	}
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_wanderSprite.setTexture(m_wanderTexture);
	//college pc 
	//m_alienSprite.setPosition(500.0f, 500.0f);
	//m_alienSprite.scale(5.0f, 5.0f);
	// my pc

	m_wanderSprite.setPosition(500.0f, 500.0f);
	m_wanderSprite.scale(3.0f, 3.0f);
	m_wanderSprite.rotate(angle);
	m_wanderSprite.setOrigin(16.0f, 16.0f);
	m_wanderSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	radius.setFillColor(sf::Color{ 107, 217, 231, 70 });
	radius.setRadius(radiusF);
	radius.setPosition(m_wanderSprite.getPosition().x - radiusF, m_wanderSprite.getPosition().y - radiusF);

	nameTag.setFont(m_font);
	nameTag.setScale(0.5f, 0.5f);
	nameTag.setString("Wander");
}

void Wander::kinematicWander(sf::Time& t_deltaTime)
{

	angle = m_wanderSprite.getRotation();
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
	linePoint.x = m_wanderSprite.getPosition().x + radiusF * cos(angleInRads);
	linePoint.y = m_wanderSprite.getPosition().y + radiusF * sin(angleInRads);

	std::cout << "Alien angle: " << angle << std::endl;
	vel.x = speed * sin(angle * t_deltaTime.asMilliseconds() / 1000);
	vel.y = speed * -cos(angle * t_deltaTime.asMilliseconds() / 1000);
	float squareAns = sqrt((vel.x * vel.x) + (vel.y * vel.y));
	sf::Vector2f normalisedVelocity = vel / squareAns;
	m_wanderSprite.move(vel);
	m_wanderSprite.setRotation(angle);
	radius.move(vel);
}



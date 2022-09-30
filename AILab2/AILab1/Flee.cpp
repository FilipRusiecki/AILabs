#include "Flee.h"

Flee::Flee()
{
	setupSprites();
}
void Flee::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (alive == true)
	{
		flee(t_deltaTime, t_player);
		boundry();
		radius.setPosition(m_fleeSprite.getPosition().x - radiusF, m_fleeSprite.getPosition().y - radiusF);
		nameTag.setPosition(m_fleeSprite.getPosition());
	}
}

void Flee::render(sf::RenderWindow& t_window)
{
	if (alive == true)
	{
		if (tracerAlive == true)
		{
			t_window.draw(radius);
		}
		t_window.draw(m_fleeSprite);
		t_window.draw(nameTag);
	}
}


void Flee::setupSprites()
{
	if (!m_fleeTexture.loadFromFile("ASSETS\\IMAGES\\fleeShip.png"))
	{
		std::cout << "problem loading player" << std::endl;
	}
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_fleeSprite.setTexture(m_fleeTexture);

	//college pc
	m_fleeSprite.setPosition(1800.0f, 1800.0f);
	m_fleeSprite.scale(5.0f, 5.0f);

	//my pc 
	//m_fleeSprite.setPosition(700.0f, 500.0f);
	//m_fleeSprite.scale(3.0f, 3.0f);

	m_fleeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_fleeSprite.setOrigin(16.0f, 16.0f);

	radius.setFillColor(sf::Color{ 107, 217, 231, 70 });
	radius.setRadius(radiusF);
	radius.setPosition(m_fleeSprite.getPosition().x - radiusF, m_fleeSprite.getPosition().y - radiusF);

	nameTag.setString("flee");
	nameTag.setFont(m_font);
	nameTag.setScale(0.5f, 0.5f);
}

void Flee::flee(sf::Time& t_deltaTime, Player& t_player)
{
	sf::Vector2f playerpos = t_player.m_playerSprite.getPosition();
	sf::Vector2f mypos = m_fleeSprite.getPosition();
	vel = mypos - playerpos;
	distance = sqrtf(vel.x * vel.x + vel.y * vel.y);
	distanceVec = sf::Vector2f{ vel.x / distance , vel.y / distance };
	vel = distanceVec * maxSpeed;
	if (distance < radiusF)
	{ 
		radius.setFillColor(sf::Color{ 235, 64, 52, 70 });
	}
	else {
		
		radius.setFillColor(sf::Color{ 52, 235, 61, 70 });
		std::cout << "			player very close: " << rotation << std::endl;
		sf::Vector2f normalisedVelocity = { vel.x / distance ,vel.y / distance };
		vel = normalisedVelocity;
		vel = vel * maxSpeed;
		//vel = vel *maxSpeed;
		
	}

	float dx = mypos.x - playerpos.x;
	float dy = mypos.y - playerpos.y;
	GetProperRot = (atan2(dy, dx)) * 180 / pi;
	rotation = GetProperRot + 90;
	m_fleeSprite.setRotation(rotation);
	std::cout << "									Flee angle: " << rotation << std::endl;
	m_fleeSprite.move(vel);

}

void Flee::boundry()
{
	//moving left off screen
	if (m_fleeSprite.getPosition().x > sf::VideoMode::getDesktopMode().width)
	{
		m_fleeSprite.setPosition(0 , m_fleeSprite.getPosition().y);
	}

	//moving right of screen 
	if (m_fleeSprite.getPosition().x < 0 )
	{
		m_fleeSprite.setPosition(sf::VideoMode::getDesktopMode().width, m_fleeSprite.getPosition().y);
	}

	//moving top of screen 
	if (m_fleeSprite.getPosition().y < 0 )
	{
		m_fleeSprite.setPosition(m_fleeSprite.getPosition().x, sf::VideoMode::getDesktopMode().height);
	}

	//moving bottom of screen 
	if (m_fleeSprite.getPosition().y > sf::VideoMode::getDesktopMode().height)
	{
		m_fleeSprite.setPosition(m_fleeSprite.getPosition().x, 0 );
	}

}

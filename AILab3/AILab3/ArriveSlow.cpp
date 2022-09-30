#include "ArriveSlow.h"


ArriveSlow::ArriveSlow()
{
	setupSprites();
}

void ArriveSlow::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (alive == true)
	{
		seek(t_deltaTime, t_player);
		nameTag.setPosition(m_arrvieSprite.getPosition());
	}
}

void ArriveSlow::render(sf::RenderWindow& t_window)
{
	if (alive == true)
	{
		if (tracerAlive == true)
		{
			t_window.draw(LineToPlayer);
		}
		t_window.draw(m_arrvieSprite);
		t_window.draw(nameTag);
	}
}



void ArriveSlow::setupSprites()
{
	if (!m_arrvieTexture.loadFromFile("ASSETS\\IMAGES\\arriveShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading npc" << std::endl;
	}
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_arrvieSprite.setTexture(m_arrvieTexture);
	//college pc 
	//m_m_seekSpriteSprite.setPosition(1200.0f, 500.0f);
	//m_m_seekSpriteSprite.scale(5.0f, 5.0f);
	// my pc
	m_arrvieSprite.setPosition(500.0f, 500.0f);
	m_arrvieSprite.scale(3.0f, 3.0f);
	m_arrvieSprite.rotate(angle);
	m_arrvieSprite.setOrigin(16.0f, 16.0f);
	m_arrvieSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	nameTag.setFont(m_font);
	nameTag.setScale(0.5f, 0.5f);
	nameTag.setString("ArriveSlow");
}

void ArriveSlow::seek(sf::Time& t_deltaTime, Player& t_player)
{
	sf::Vector2f playerpos = t_player.m_playerSprite.getPosition();
	sf::Vector2f mypos = m_arrvieSprite.getPosition();

	vel = playerpos - mypos; //Velocity = target.position - my.position

	distance = sqrtf(vel.x * vel.x + vel.y * vel.y);
	distanceVec = sf::Vector2f{ vel.x / distance , vel.y / distance };
	vel = distanceVec * maxSpeed;
	if (distance > t_player.radiusF)
	{
		std::cout << "		SEEKING PLAYER			" << std::endl;
	}
	else {
		vel = vel / timeToTarget;
		if (distance > maxSpeed)
		{

			std::cout << "		IN PLAYER RADIUS			" << std::endl;
			sf::Vector2f normalisedVelocity = { vel.x / distance ,vel.y / distance };
			vel = normalisedVelocity;
			vel = vel * maxSpeed * 2.0f;
		}
		if (distance < t_player.radiusFSmall)
		{
			std::cout << "		BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP			" << std::endl;
			vel = { 0.0f,0.0f };
		}
	}
	float dx = mypos.x - playerpos.x;
	float dy = mypos.y - playerpos.y;
	GetProperRot = (atan2(dy, dx)) * 180 / pi;
	rotation = GetProperRot - 90;
	m_arrvieSprite.setRotation(rotation);
	std::cout << "				Seek angle: " << rotation << std::endl;
	m_arrvieSprite.move(vel);
	LineToPlayer.clear();
	sf::Vertex begin{ mypos,sf::Color::Transparent };
	LineToPlayer.append(begin);
	sf::Vertex end{ playerpos, sf::Color::Red };
	LineToPlayer.append(end);
}


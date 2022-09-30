#include "Arrive.h"

Arrive::Arrive()
{
	setupSprites();
}

void Arrive::update(sf::Time& t_deltaTime, Player& t_player)
{	
	kinematicWander(t_deltaTime, t_player);
}

void Arrive::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_arriveSprite);
	
}

void Arrive::setupSprites()
{
	if (!m_arriveTexture.loadFromFile("ASSETS\\IMAGES\\playerShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading npc" << std::endl;
	}
	m_arriveSprite.setTexture(m_arriveTexture);
	//college pc 
	//m_arriveSprite.setPosition(700.0f, 700.0f);
	//m_arriveSprite.scale(5.0f, 5.0f);



	// my pc
	m_arriveSprite.setPosition(200.0f, 500.0f);
	m_arriveSprite.scale(3.0f, 3.0f);
	m_arriveSprite.rotate(angle);
	m_arriveSprite.setOrigin(16.0f, 16.0f);
	m_arriveSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

}

void Arrive::kinematicWander(sf::Time& t_deltaTime,Player& t_player)
{
	angle = m_arriveSprite.getRotation();
	angle = angle + randomInt;

	if (angle == 360.0)
	{
		angle = 0;
	}
	if (angle == 0.0)
	{
		angle = 359.0;
	}
	

	//vel.x = speed * sin(m_arriveSprite.getRotation() * t_deltaTime.asMilliseconds() / 1000);
	//vel.y = speed * -cos(m_arriveSprite.getRotation() * t_deltaTime.asMilliseconds() / 1000);

	//std::cout << m_mouseLocation.x << m_mouseLocation.y << std::endl;
	vel = t_player.m_playerSprite.getPosition() - m_arriveSprite.getPosition(); 
	vel = vel / timeToTarget;
	m_distance = sqrtf(vel.x * vel.x + vel.y * vel.y);
	vel = sf::Vector2f{ vel.x / m_distance , vel.y / m_distance };
	vel = vel * speed;

	//m_distance = sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y); //Calculate the length between two points 
	//m_unitVector = sf::Vector2f{ m_direction.x / m_distance , m_direction.y / m_distance }; //Calculate unit vector
	//m_direction = m_unitVector; //Set the direction properly

	

	m_arriveSprite.move(vel);

	//m_arriveSprite.setRotation(angle);
}

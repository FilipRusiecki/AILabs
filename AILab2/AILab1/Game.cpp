
#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, sf::VideoMode::getDesktopMode().bitsPerPixel}, "AILab1" },
	m_exitGame{ false } //when true game will exit
{
	playerOffScreenOffsetX = myPlayer.m_playerSprite.getGlobalBounds().width;
	playerOffScreenOffsetY = myPlayer.m_playerSprite.getGlobalBounds().height;
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;

	}
	info.setFont(m_font);
	info.setScale(1.0f, 1.0f);
	info.setString("Press 1: NPC , 2:Wander , 3:Seek/Arrive , 4: Flee , 5:TracerLines\n L: player speed = 0, K: player speed = 2, J: player speed = 5");
	info.setPosition(10.0f, 10.0f);
}


Game::~Game()
{

}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps

	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps

		}
		render(); // as many as possible
	}
}
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		myNpc.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		myAlien.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		mySeek.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		myFlee.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		myPlayer.tracerAlive  ^= true;
		myAlien.tracerAlive ^= true;
		mySeek.tracerAlive ^= true;
		myFlee.tracerAlive ^= true;
	}
}
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	myPlayer.update(t_deltaTime);
	myNpc.update();
	myAlien.update(t_deltaTime);
	mySeek.update(t_deltaTime, myPlayer);
	myFlee.update(t_deltaTime, myPlayer);
}


void Game::render()
{
	m_window.clear(sf::Color::Black);
	myNpc.reder(m_window);
	myPlayer.reder(m_window);
	myAlien.render(m_window);
	myFlee.render(m_window);
	mySeek.render(m_window); 
	m_window.draw(info);
	m_window.display();
}




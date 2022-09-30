/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>




Game::Game() :
	m_window{ sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, sf::VideoMode::getDesktopMode().bitsPerPixel}, "AILab1"},
	m_exitGame{false} //when true game will exit
{
	playerOffScreenOffsetX = myPlayer.m_playerSprite.getGlobalBounds().width;
	playerOffScreenOffsetY = myPlayer.m_playerSprite.getGlobalBounds().height;

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

void Game::checkForOffScreen()
{
	//player moving left off screen
	if (myPlayer.m_playerSprite.getPosition().x > sf::VideoMode::getDesktopMode().width)
	{	
		myPlayer.m_playerSprite.setPosition(0- playerOffScreenOffsetX, myPlayer.m_playerSprite.getPosition().y);
	}

	//player moving right of screen 
	if (myPlayer.m_playerSprite.getPosition().x < 0 - playerOffScreenOffsetX)
	{
		myPlayer.m_playerSprite.setPosition(sf::VideoMode::getDesktopMode().width, myPlayer.m_playerSprite.getPosition().y);
	}

	//player moving top of screen 
	if (myPlayer.m_playerSprite.getPosition().y < 0 - playerOffScreenOffsetY)
	{
		myPlayer.m_playerSprite.setPosition(myPlayer.m_playerSprite.getPosition().x, sf::VideoMode::getDesktopMode().height);
	}

	//playe rmoving bottom of screen 
	if (myPlayer.m_playerSprite.getPosition().y > sf::VideoMode::getDesktopMode().height)
	{
		myPlayer.m_playerSprite.setPosition(myPlayer.m_playerSprite.getPosition().x, 0 - playerOffScreenOffsetY);
	}


	//npc moving top of screen 
	if (myNpc.m_npcSprite.getPosition().y < 0 - playerOffScreenOffsetY)
	{
		myNpc.m_npcSprite.setPosition(myNpc.m_npcSprite.getPosition().x, sf::VideoMode::getDesktopMode().height);
	}

}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
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

}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	checkForOffScreen();
	myPlayer.update();
	myNpc.update();




}


void Game::render()
{
	m_window.clear(sf::Color::Black);
	myNpc.reder(m_window);
	myPlayer.reder(m_window);
	m_window.display();
}




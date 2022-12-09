

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1920U, 1080U, 32U }, "FuzzyGame" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
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
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}


void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_message);
	myPlayer.draw(m_window);
	m_window.display();
}


void Game::setupFontAndText()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\Pixellari.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_message.setFont(m_font);
	m_message.setString("Fuzzy Game");
	m_message.setStyle(sf::Text::Bold);
	m_message.setPosition(40.0f, 40.0f);
	m_message.setCharacterSize(80U);
	m_message.setFillColor(sf::Color::Red);
	

}


void Game::setupSprite()
{

}
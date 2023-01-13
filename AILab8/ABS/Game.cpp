
#include "Game.h"
#include "MoveTo.h"
#include "MoveAway.h"
#include "Wander.h"
#include "Repeat.h"
#include "Sequence.h"
#include "Selector.h"
#include "IsDroidInRange.h"
#include "RunChildAndIgnoreResult.h"
#include "CheckForAlarms.h"
#include "GetHealth.h"
#include "IsHealthLow.h"
#include "Hide.h"
#include "Protect.h"
#include "Protect2.h"
#include <iostream>
#include <list>

using namespace std;

Game::Game() :
	//m_window{ sf::VideoMode{ 1400, 1100, 32 }, "Droid Behaviour" },
	m_window{ sf::VideoMode{ 1000, 800, 32 }, "Droid Behaviour Tree Example" },
	m_exitGame{ false } //when true game will exit
{

	setupFontAndText(); // load font 
	setupDroids(); // load texture
	setupGrid(); // Prepare the grid world
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
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
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event t_event;
	while (m_window.pollEvent(t_event))
	{
		if (sf::Event::Closed == t_event.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == t_event.type) //user pressed a key
		{
			processKeys(t_event);
		}
//		if (sf::Event::MouseButtonPressed == t_event.type || sf::Event::MouseButtonReleased == t_event.type) //user pressed a key
		{
			// I always call processMouse for the case when the middle mouse button is held down to draw obstacles.
			processMouse(t_event);
		}
	}
}

/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Event::Closed == t_event.type) // window message
	{
		m_window.close();
	}
	if (sf::Event::KeyPressed == t_event.type) //user key press
	{
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			m_exitGame = true;
		}
		if (sf::Keyboard::T == t_event.key.code) {
		}
		if (sf::Keyboard::C == t_event.key.code) {
		}
		if (sf::Keyboard::F == t_event.key.code) {
		}
		if (sf::Keyboard::P == t_event.key.code) {
		}
		if (sf::Keyboard::Num1 == t_event.key.code) {
		}
	}
}

/// <summary>
/// deal with mouse button presses from the user
/// </summary>
/// <param name="t_event">mouse press event</param>
void Game::processMouse(sf::Event t_event)
{
	//check for mouse click.
		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			//Gets mouse coordinates
			sf::Vector2i mouseCoords = sf::Mouse::getPosition(m_window);
			//			std::cout << "Mouse X: " << mouseCoords.x << " " << "Mouse Y: " << mouseCoords.y <<  std::endl;

			goalX = gridWorld.getGridCellX(mouseCoords);
			goalY = gridWorld.getGridCellY(mouseCoords);
			goalSet = true;
			if (goalX <= 0 || goalY <= 0 || goalX > gridWorld.gridSize || goalY > gridWorld.gridSize)	// Check we clicked in the grid
				goalSet = false;			
		}
		else if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Right)
		{
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
		}
		else if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Middle)
		{
		}
}


/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	updateDroids();

}

void Game::updateDroids()
{
	for (Droid* d : m_droids)
	{
		// If a droid's behaviour completed we can kick it off again from the root.
		if (d->name == "D2" && (d->getBehaviour()->isSuccess() || d->getBehaviour()->isFailure()))
			d->getBehaviour()->reset(" from the main Game loop.");
		if (d->name == "D3" && d->getBehaviour()->isSuccess())
			d->getBehaviour()->reset(" from the main Game loop.");
		if (d->name == "D4" && d->getBehaviour()->isSuccess())
			d->getBehaviour()->reset(" from the main Game loop.");
		if (d->name == "D5" && d->getBehaviour()->isSuccess())
			d->getBehaviour()->reset(" from the main Game loop.");
		if (d->name == "D6" && d->getBehaviour()->isSuccess())
			d->getBehaviour()->reset(" from the main Game loop.");
		//if (d->name == "D10" && (d->getBehaviour()->isSuccess() || d->getBehaviour()->isFailure()))	// Demonstrating a continuous check for danger
		//{
		//	d->getBehaviour()->reset(" from the main Game loop.");
		//	d->getBrain()->reset(" from the main Game loop.");
		//}
		if (d->name == "D1")	// Move to where the mouse has been clicked
		{
			if (goalSet)
			{
				goalSet = false;
				Routine* moveToGoal = new MoveTo(goalX, goalY, gridWorld);
				d->setBehaviour(moveToGoal);
				d->getBehaviour()->reset(" from the main Game loop.");
			}

		}
		d->update(gridWorld);
	}

}

void Game::render()
{
	m_window.clear(sf::Color::White);
	drawGrid(m_window);
	drawDroids(m_window);
	drawHealthPills(m_window);

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
}

/// <summary>
/// Create a list of Droids
/// </summary>
void Game::setupDroids()
{
	Routine* emptyBrain = new Routine();

	// Example Droid with a simple MoveTo Behaviour
	// Droid d1 will also follow the mouse clicks within the update loop
	Droid *d1 = new Droid("D1", 5, 5, 1000, 0, gridWorld);
	Routine* moveTo1 = new MoveTo(5, 10, gridWorld);
	d1->setBehaviour(moveTo1);
	d1->target = gridWorld.getGridLocation(7, 9);
	d1->setBrain(emptyBrain);
	// The default droid colour is Yellow.
	
	// Example Droid with a simple MoveTo Behaviour
	Droid* d2 = new Droid("D2", (rand() % (int)gridWorld.gridSize) + 1, (rand() % (int)gridWorld.gridSize) + 1, 1000, 0, gridWorld);
	Routine* moveTo2 = new MoveTo(15, 15, gridWorld);
	d2->setBehaviour(moveTo2);
	d2->setBrain(emptyBrain);
	d2->droidSprite.setColor(sf::Color::Green);

	// Example Droid with a simple Wnader Behaviour
	// Remember that when a behviour SUCCEEDs then it is finished, so in updateDroids() I reset this brain so it will wander again.
	Droid* d3 = new Droid("D3", 20, 3, 1000, 0, gridWorld);
	Routine* wander3 = new Wander(gridWorld);
	d3->setBehaviour(wander3);
	d3->setBrain(emptyBrain);
	d3->droidSprite.setColor(sf::Color::Magenta);

	// Example Droid with a Hide Behaviour
	Droid* d4 = new Droid("D4", (rand() % (int)gridWorld.gridSize) + 1, (rand() % (int)gridWorld.gridSize) + 1, 1000, 0, gridWorld);
	Routine* hide4 = new Hide(1, 2, gridWorld);	// Hide behind D2 from D1
	d4->setBehaviour(hide4);
	d4->setBrain(emptyBrain);
	d4->droidSprite.setColor(sf::Color::Cyan);

	// Example Droid with a protect Behaviour
	// ...
	Droid* d5 = new Droid("D5", (rand() % (int)gridWorld.gridSize) + 1, (rand() % (int)gridWorld.gridSize) + 1, 1000, 0, gridWorld);
	Routine* protect = new Protect(1, 2, gridWorld);	// Hide behind D2 from D1
	d5->setBehaviour(protect);
	d5->setBrain(emptyBrain);
	d5->droidSprite.setColor(sf::Color::Blue);
	// ...

	// Example Droid with a Selector Behaviour
	// Check for enemies nearby, if found then MoveAway otherwise continue

	//emptyBrain = new CheckForAlarms();
	//Droid* d6 = new Droid("D6", 20, 20, 1000, 0, gridWorld);
	//Selector* selectorD6 = new Selector();
	//Sequence* sequenceD6 = new Sequence();
	//Routine* isDroidInRangeD6 = new IsDroidInRange(3);
	//Routine* moveAwayD6 = new MoveAway(3, gridWorld);
	//sequenceD6->addRoutine(isDroidInRangeD6);
	//sequenceD6->addRoutine(moveAwayD6);
	//Routine* wander6 = new Wander(gridWorld);
	//selectorD6->addRoutine(sequenceD6);
	//selectorD6->addRoutine(wander6);
	//d6->setBehaviour(selectorD6);
	//d6->setBrain(emptyBrain);
	//d6->droidSprite.setColor(sf::Color::Black);

	Droid* d6 = new Droid("D6", (rand() % (int)gridWorld.gridSize) + 1, (rand() % (int)gridWorld.gridSize) + 1, 1000, 0, gridWorld);
	Routine* protect2 = new Protect2(1, 2, gridWorld);	// Hide behind D2 from D1
	d6->setBehaviour(protect2);
	d6->setBrain(emptyBrain);
	d6->droidSprite.setColor(sf::Color::Blue);


	m_droids.push_back(d1);
	m_droids.push_back(d2);
	//m_droids.push_back(d3);
	m_droids.push_back(d4);
	m_droids.push_back(d5);
	m_droids.push_back(d6);
	//m_droids.push_back(d6);

	gridWorld.m_gridDroids = m_droids;	//So we can access them when inside the behaviours.

	int x = gridWorld.getGridCellX(sf::Vector2i(400, 300));

}

/// <summary>
/// Run through the grid and setup obstacles
/// </summary>
void Game::initGridObjects()
{
	int hpx = rand() % gridWorld.gridSize + 1;
	int hpy = rand() % gridWorld.gridSize + 1;
	HealthPill* h1 = new HealthPill(hpx, hpy, 50, true, gridWorld);
	hpx = rand() % gridWorld.gridSize + 1;
	hpy = rand() % gridWorld.gridSize + 1;
	HealthPill* h2 = new HealthPill(hpx, hpy, 50, true, gridWorld);
	hpx = rand() % gridWorld.gridSize + 1;
	hpy = rand() % gridWorld.gridSize + 1;
	HealthPill* h3 = new HealthPill(hpx, hpy, 50, true, gridWorld);
	hpx = rand() % gridWorld.gridSize + 1;
	hpy = rand() % gridWorld.gridSize + 1;
	HealthPill* h4 = new HealthPill(hpx, hpy, 50, true, gridWorld);
	hpx = rand() % gridWorld.gridSize + 1;
	hpy = rand() % gridWorld.gridSize + 1;
	HealthPill* h5 = new HealthPill(hpx, hpy, 50, true, gridWorld);
	m_healthPills.push_back(h1);
	m_healthPills.push_back(h2);
	m_healthPills.push_back(h3);
	m_healthPills.push_back(h4);
	m_healthPills.push_back(h5);

	gridWorld.m_gridHealthPills = m_healthPills;	//So we can access them when inside the behaviours.
}


/// <summary>
/// Initialsie the grid at startup.
/// Add in obstacles here.
/// </summary>
void Game::setupGrid()
{
	initGridObjects(); // HealthPills etc

}

/// <summary>
/// Draw the grid cells
/// </summary>
void Game::drawGrid(sf::RenderWindow& t_window)
{
	gridWorld.draw(m_window);
}

void Game::drawDroids(sf::RenderWindow& t_window)
{
	for (Droid* d : m_droids)
	{
		d->draw(t_window, gridWorld);
	}
}

void Game::drawHealthPills(sf::RenderWindow& t_window)
{
	for (HealthPill* hp : m_healthPills)
	{
		hp->draw(t_window, gridWorld);
	}
}



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
	if (sf::Keyboard::F == t_event.key.code)
	{
		resetEnemies = true;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	
	if (m_exitGame)
	{
		m_window.close();
	}

	if (resetEnemies == true)
	{
		randomAmountOfEnemies = rand() % 30 + 1;
		reset();
		Ui1.setString("Force: " + std::to_string(force));
		Ui2.setString("Range: " + std::to_string(range));
	}

}


void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_message);
	m_window.draw(m_message1);
	m_window.draw(UiBox);
	m_window.draw(Ui1);
	m_window.draw(Ui2);
	m_window.draw(Ui3);
	m_window.draw(Ui4);
	m_window.draw(Ui5);
	m_window.draw(Ui6);


	myPlayer.draw(m_window);
	for (int i = 0; i < randomAmountOfEnemies; i++)
	{
		myEnemy[i].draw(m_window);
		myEnemy[i].alive = true;

	}
	m_window.display();
}


void Game::setupFontAndText()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\Pixellari.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_message.setFont(m_font);
	m_message.setString("Fuzzy Logic");
	m_message.setStyle(sf::Text::Bold);
	m_message.setPosition(40.0f, 40.0f);
	m_message.setCharacterSize(80U);
	m_message.setFillColor(sf::Color::Red);


	m_message1.setFont(m_font);
	m_message1.setString("press F to randomize Enemies");
	m_message1.setStyle(sf::Text::Bold);
	m_message1.setPosition(48.0f, 150.0f);
	m_message1.setCharacterSize(20U);
	m_message1.setFillColor(sf::Color::Green);

	Ui1.setFont(m_font);
	Ui1.setString("Ui1");
	Ui1.setStyle(sf::Text::Bold);
	Ui1.setPosition(48.0f, 650.0f);
	Ui1.setCharacterSize(30U);
	Ui1.setFillColor(sf::Color::Cyan);
	Ui1.setOutlineThickness(1.0f);
	Ui1.setOutlineColor(sf::Color::Black);

	Ui2.setFont(m_font);
	Ui2.setString("Ui2");
	Ui2.setStyle(sf::Text::Bold);
	Ui2.setPosition(48.0f, 680.0f);
	Ui2.setCharacterSize(30U);
	Ui2.setFillColor(sf::Color::Cyan);
	Ui2.setOutlineThickness(1.0f);
	Ui2.setOutlineColor(sf::Color::Black);

	Ui3.setFont(m_font);
	Ui3.setString("Ui3");
	Ui3.setStyle(sf::Text::Bold);
	Ui3.setPosition(48.0f, 710.0f);
	Ui3.setCharacterSize(30U);
	Ui3.setFillColor(sf::Color::Cyan);
	Ui3.setOutlineThickness(1.0f);
	Ui3.setOutlineColor(sf::Color::Black);

	Ui4.setFont(m_font);
	Ui4.setString("Ui4");
	Ui4.setStyle(sf::Text::Bold);
	Ui4.setPosition(48.0f, 740.0f);
	Ui4.setCharacterSize(30U);
	Ui4.setFillColor(sf::Color::Cyan);
	Ui4.setOutlineThickness(1.0f);
	Ui4.setOutlineColor(sf::Color::Black);

	Ui5.setFont(m_font);
	Ui5.setString("Ui5");
	Ui5.setStyle(sf::Text::Bold);
	Ui5.setPosition(48.0f, 770.0f);
	Ui5.setCharacterSize(30U);
	Ui5.setFillColor(sf::Color::Cyan);
	Ui5.setOutlineThickness(1.0f);
	Ui5.setOutlineColor(sf::Color::Black);

	Ui6.setFont(m_font);
	Ui6.setString("Ui6");
	Ui6.setStyle(sf::Text::Bold);
	Ui6.setPosition(48.0f, 800.0f);
	Ui6.setCharacterSize(30U);
	Ui6.setFillColor(sf::Color::Cyan);
	Ui6.setOutlineThickness(1.0f);
	Ui6.setOutlineColor(sf::Color::Black);
}


void Game::setupSprite()
{
	UiBox.setSize(sf::Vector2f(330,240));
	UiBox.setFillColor(sf::Color(110, 115, 111, 60));
	UiBox.setPosition(43,646);
}

void Game::spreadEnemies()
{
	float randomX = rand() % 1500 + 200;
	Y = 100;

	for (int i = 0; i < 30; i++)
	{	
		Y += 25;
		myEnemy[i].circle.setPosition(randomX, Y);
	}
	force = randomAmountOfEnemies;
	range = randomX;
}

void Game::reset()
{
	resetEnemies = false;
	spreadEnemies();
	settingRangeAndForce();
	threatLevelApplication();
	defuzzification();
}

void Game::threatLevelApplication()
{
	lowDanger = FuzzyOR(FuzzyOR(FuzzyAND(mediumRange, tinyForce), FuzzyAND(mediumRange, smallForce)), FuzzyAND(largeRange, FuzzyNOT(largeForce)));
	moderateDanger = FuzzyOR(FuzzyOR(FuzzyAND(closeRange, tinyForce), FuzzyAND(mediumRange, moderateForce)), FuzzyAND(largeRange, largeForce));
	highDanger = FuzzyOR(FuzzyAND(closeRange, FuzzyNOT(tinyForce)), FuzzyAND(mediumRange, largeForce));

	Ui4.setString("LowDanger: " + std::to_string(lowDanger));
	Ui5.setString("MidDanger: " + std::to_string(moderateDanger));
	Ui6.setString("HighDanger: " + std::to_string(highDanger));

}

double Game::FuzzyTrapezoid(double v, double x0, double x1, double x2, double x3)
{
	double result = 0;
	double x = v;

	if ((x <= x0) || (x >= x3))
	{
		result = 0.0;
	}
	else if ((x >= x1) && (x <= x2))
	{
		result = 1.0;
	}
	else if ((x > x0) && (x < x1))
	{
		result = ((x- x0) / (x1-x0));
	}
	else
	{
		result = ((x3 - x) / (x3 - x2));
	}
	return 0.0;
}

double Game::FuzzyTriangle(double v, double x0, double x1, double x2)
{
	double result = 0;
	double x = v;

	if ((x <= x0) || (x >= x2))
	{
		result = 0;
	}
	else if (x == x1)
	{
		result = 1;
	}
	else if ((x > x0) && (x < x1))
	{
		result = ((x - x0) / (x1 - x0));
	}
	else {
		result = ((x2 - x) / (x2 - x1));
		return result;
	}
}

double Game::FuzzyGrade(double v, double x0, double x1)
{
	double result = 0;
	double x = v;

		if(x <= x0)
		{
			result = 0;
		}
		else if (x > x1)
		{
			result = 1;
		}
		else
		{
			result = ((x - x0) / (x1 - x0));
			return result;
		}
}

double Game::FuzzyAND(double A, double B)
{
	return std::min(A, B);
}

double Game::FuzzyOR(double A, double B)
{
	return std::max(A, B);
}

double Game::FuzzyNOT(double A)
{
	return 1.0 - A;
}

void Game::settingRangeAndForce()
{

	tinyForce = FuzzyTriangle(force,0,4,9);
	smallForce = FuzzyTrapezoid(force,2,9,15,18);
	moderateForce = FuzzyTrapezoid(force,15,18,21,25);
	largeForce = FuzzyGrade(force,21,25);



	closeRange = FuzzyTriangle(range,200,500,800);
	mediumRange = FuzzyTrapezoid(range,500,800,1200,1400);
	largeRange = FuzzyGrade(range,1200,1700);

}

void Game::defuzzification()
{
	double nDeploy = 0;
	nDeploy = (lowDanger * 10 + moderateDanger * 30 + highDanger * 50) / (lowDanger + moderateDanger + highDanger);
	Ui3.setString("defuzz: " + std::to_string(nDeploy));
}





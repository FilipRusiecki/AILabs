/// 
/// @author Dr. Oisin Cawley
/// @date March 2021

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 


#include "Game.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>

using namespace std;

// Updates as milliseconds
static double const S_PER_UPDATE = 5;

/// <summary>
/// Default constructor
/// 
/// 
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(Game::width, Game::height), "AI for Flappy Bird - ANN trained via Backpropagation"),
	m_exitGame{ false } //when true game will exit

{
	m_window.setFramerateLimit(10); //Lets start slow so we can see whats going on.

	if (!font.loadFromFile("Assets\\ariblk.ttf"))
	{
		std::cout << "could not load font" << std::endl;
	}

	text.setFont(font);
	text.setString("Evolutionary Details");
	// in pixels, not points!
	text.setCharacterSize(10);
	text.setPosition(sf::Vector2f(10, 10));
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(10);

}

/// <summary>
/// Default destructor
/// 
/// 
/// </summary>
Game::~Game()
{
}

void Game::init()
{
	srand(time(NULL));

	for (int i = 0; i < pillarCount; i++)
	{
		pillarSet[i].init(width / 2.5 + (i * pillarGap));
	}
	population.createPopulation(birdCount);
	if (ai)
	{
		for (int b = 0; b < birdCount; b++)
		{
			population.birdSet[b].y = rand() % Game::height;	// Since we have more than 1 AI bird we will reset it to a random vertical position
			loadTFBrain(b);	// Load network weights from Tensorflow file
		}
	}
	loop();
}


/// <summary>
/// Train the neural netork from training data in a file.
/// Doing the training in Python with Tensorflow.
/// Just loading those weights into the Brid's neural network.
/// </summary>
void Game::loadTFBrain(int bird)
{
	vector<string> row;
	string line, word, temp;
	int layer = 0;
	int index = 0;
	float weight = 0.0f;

//	myWeightsFile.open("flappy_tf_weights.csv");
	myWeightsFile.open("flappy_tf_weights-21k-Acc76point84.csv");
//	myWeightsFile.open("flappy_tf_weights-70k-Acc78point44.csv");

	while (!myWeightsFile.eof())
	{
		// First 5 lines are the weights for the inputs to the hidden layer;
		for (int i = 0; i < 5; i++)
		{
			row.clear();
			// read an entire row and 
			// store it in a string variable 'line' 
			getline(myWeightsFile, line);
			std::cout << line << std::endl;

			// used for breaking words 
			stringstream s(line);
			// read every column data of a row and 
			// store it in a string variable, 'word'
			index = 0;
			while (getline(s, word, ','))
			{
				weight = stof(word);
				population.birdSet[bird].brain.weightsLayer1[i][index] = weight;
				std::cout << "Inputs to Hidden: " << weight << std::endl;
				index = index + 1;
			}
		}
		// Next 4 lines are the bias weights to the hidden layer;
		for (int i = 0; i < 4; i++)
		{
			getline(myWeightsFile, line);
			stringstream s(line);
			while (getline(s, word, ','))
			{
				weight = stof(word);
				population.birdSet[bird].brain.biases[i] = weight;
				std::cout << "Bias for neuron " << i+1 << ": " << weight << std::endl;
			}
		}
		// Next 4 lines are the input weights to the output layer;
		for (int i = 0; i < 4; i++)
		{
			getline(myWeightsFile, line);
			stringstream s(line);
			while (getline(s, word, ','))
			{
				weight = stof(word);
				population.birdSet[bird].brain.weightsLayer2[i] = weight;
				std::cout << "Hidden to Outputs: " << weight << std::endl;
			}
		}
		// Last line is the bias weight to the output neuron
		for (int i = 0; i < 1; i++)
		{
			getline(myWeightsFile, line);
			stringstream s(line);
			while (getline(s, word, ','))
			{
				weight = stof(word);
				population.birdSet[bird].brain.biases[4] = weight;
				std::cout << "Bias for output neuron: " << weight << std::endl;
			}
		}
	}
	myWeightsFile.close();
}


/// <summary>
/// The game loop, listens for key press events and handles window closing,
/// calls the update and draw methods
/// </summary>
void Game::loop()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 40.f); // 60 fps
	if (player)
		timePerFrame = sf::seconds(1.f / 30.f); // 60 fps

	sf::Int32 lag = 0;
	int num = 0;

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			// window closed
			case sf::Event::Closed:		//Window message
				if (myTrainingfile.is_open())
					myTrainingfile.close();
				m_window.close();
				break;
			// key pressed
			case sf::Event::KeyPressed:
				if (sf::Keyboard::Escape == event.key.code)
				{
					m_exitGame = true;
				}
				// Moved this into the update function since it doesn't get called quickly enough inside this pollEvent.
//				if ((sf::Keyboard::Space == event.key.code) && (player))
//				{
//					population.birdSet[0].jump = true;
//				}
				if (sf::Keyboard::S == event.key.code)
				{
					showBirdStats = !showBirdStats;
				}
				if (sf::Keyboard::R == event.key.code)
				{
					render = !render;
				}
				if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9)
				{
					currentSpeed = event.key.code - sf::Keyboard::Num0;
					int frameRate = (event.key.code - sf::Keyboard::Num0);
					timePerFrame = sf::seconds(1.f / (40.f * frameRate));
//					m_window.setFramerateLimit(frameRate);
				}
				// Start capturing the environment inputs and bird brain decisions for training data.
				if (sf::Keyboard::C == event.key.code)
				{
					string w = "";
					if (!capture)
					{
						capture = true;
						std::cout << "======================" << std::endl;
						myTrainingfile.open("training_data.csv");
					}
					else
					{
						capture = false;	// Turn it off
						if (myTrainingfile.is_open())
							myTrainingfile.close();
					}
				}
			default:
				break;
			}
		}
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(S_PER_UPDATE);
		}
		if (render) draw();
	}
}


/// <summary>
/// Update the game also update the collision with the screen and wrap entities around
/// TODO: make sure the collision off the screen is handled INSIDE the object class, create
/// a static window variable public to all objects
/// 
/// 
/// </summary>
void Game::update(float dt)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (player))
	{
		population.birdSet[0].jump = true;
	}

	for (int i = 0; i < pillarCount; i++)
	{
		pillarSet[i].update(dt, pillarSet);

	}
	int birdsAlive = 0;
	birdsAlive = population.update(pillarSet[index]);
	if (birdsAlive == 0)
	{
		if (player || ai)
			m_exitGame = true;
	}
	else if (capture)	// Capture training data.
	{
		string tempString = "";

		for (int b = 0; b < birdCount; b++)
		{
			if (population.birdSet[b].alive)
			{
				tempString = to_string(pillarSet[index].x) + "," + to_string(pillarSet[index].upperH) + "," + to_string(pillarSet[index].lowerY);
				tempString = tempString + "," + to_string(population.birdSet[b].x) + "," + to_string(population.birdSet[b].y);

//				myTrainingfile << tempString;
				if (population.birdSet[b].jump)
				{
					tempString = tempString + ",flap";
//					myTrainingfile << ",flap\n";
				}
				else
					tempString = tempString + ",glide";
					//myTrainingfile << ",glide\n";

				std::cout << tempString << std::endl;
				tempString = tempString + "\n";	// Add the newline here so that it doesn't mess up the console output.
				myTrainingfile << tempString;
			}
		}
	}
	if (ai)		// Lets see what decisions the network is making
	{
		string tempString = "";
		tempString = to_string(pillarSet[index].x) + "," + to_string(pillarSet[index].upperH) + "," + to_string(pillarSet[index].lowerY);
		tempString = tempString + "," + to_string(population.birdSet[0].x) + "," + to_string(population.birdSet[0].y);
		tempString = tempString + (population.birdSet[0].jump ? ",flap" : ",glide");
		std::cout << tempString << std::endl;

	}
	// So for the case where player has pressed space and we have captured it for training we must reset the flag.
	if (player)
		population.birdSet[0].jump = false;

}

/// <summary>
/// Draw the game entities
/// 
/// 
/// </summary>
void Game::draw()
{
	m_window.clear();
	for (int i = 0; i < pillarCount; i++)
	{
		pillarSet[i].draw(m_window);
		// Need to keep track of which is the nearest pillar in fornt of the bird so we can draw lines to it.
		// Throw in a bit of colouring. Also helps with the debug.
		if (pillarSet[i].x < population.birdSet[0].x)
		{
			pillarSet[i].colour = sf::Color::Red;
			index = (i + 1) % pillarCount;
		}
		else
		{
			pillarSet[i].colour = sf::Color::Cyan;
		}
	}
	// The green one is the pillar coming up.
	pillarSet[index].colour = sf::Color::Green;
	//	std::cout << "Next pillar: " << index << std::endl;

	text.setFillColor(sf::Color::White);
	string AIorPlayer = ai ? "AI" : "PLAYER";
	text.setString("Mode: "+ AIorPlayer);
	text.setPosition(sf::Vector2f(10, 10));
	m_window.draw(text);

	text.setString("S to toggle Bird stats");
	text.setPosition(sf::Vector2f(10, 30));
	m_window.draw(text);

	text.setString("1 - 9 sets training speed (" + std::to_string(currentSpeed) + ")");
	text.setPosition(sf::Vector2f(10, 50));
	m_window.draw(text);

	string TorF = population.birdSet[0].brain.useBiases ? "ON" : "OFF";
	text.setString("Bias included: " + TorF);
	text.setPosition(sf::Vector2f(10, 70));
	m_window.draw(text);

	for (int i = 0; i < birdCount; i++)
	{
		if (population.birdSet[i].alive)
		{
			population.birdSet[i].draw(m_window, pillarSet[index]);
			text.setString("Bird " + std::to_string(i + 1) + " Fitness: " + std::to_string(population.birdSet[i].score));
		}
		else
		{
			text.setString("Bird " + std::to_string(i + 1) + " -DEAD-");
		}
		text.setFillColor(population.birdSet[i].colour);
		text.setPosition(sf::Vector2f(10, 150 + i * 30));
		// Drawing text to the screen seems to really slow things down, so this will allow us to have maximmum learning speed.
		if (showBirdStats)
			m_window.draw(text);

	}
	m_window.display();
}

void Game::resetPillars()
{
	for (int i = 0; i < Game::pillarCount; i++)
	{
		//		pillarSet[i] = Pillar();
		pillarSet[i].init(width / .95 + (i * pillarGap));
	}

}


#include "Population.h"
#include "Game.h"
#include <iostream>



Population::Population()
{
}

Population::~Population()
{
}

void Population::createPopulation(int populationSize)
{
	birdSet = new Bird[populationSize];
	for (int i = 0; i < populationSize; i++)
	{
		birdSet[i].init(sf::Color(rand() % (255), rand() % (255), rand() % (255)));
	}

}

// The game loop method
// We pass in the pillar it is approaching
int Population::update(Pillar pillar)
{
	int birdsAlive = 0;	// We want to know when all the Birds have died so we can evelove the next generation.
	for (int i = 0; i < Game::birdCount; i++)
	{
		if (birdSet[i].alive)
		{
			birdSet[i].update(pillar);
			birdsAlive++;
		}
	}

	return birdsAlive;
}


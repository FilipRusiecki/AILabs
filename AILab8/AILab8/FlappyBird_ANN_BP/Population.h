
#pragma once

#include "Bird.h"

class Population
{
public:
	Population();
	~Population();

	void createPopulation(int populationSize);
	int update(Pillar pillar);

	Bird *birdSet;
	Bird *newBirdSet;

	int generation = 0;

};


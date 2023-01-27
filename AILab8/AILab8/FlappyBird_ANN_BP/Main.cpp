
// Based on the Python version: https://jatinmandav.wordpress.com/2018/03/05/a-i-learns-to-play-flappy-bird/
// Ported to C++ by Dr. Oisin Cawley, IT Carlow.
// This version for demonstrating how to generate test data and export to a file to be used for training in Tensorflow.
// The trained network is then reimported back into the game and controls the bird.

// Key press option 'M' to save the current network to file.
// Key press option 'C' to start capturing the environment and neural network decision if we wanted to generate test data for example.

// See Game.h for controlling if it executes the GA to train the NN, or Player mode (press space to flap), or to load a NN from file.

#include "Game.h"

/// <summary>
/// Main entry to the program 
/// 
/// 
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
int main(int, char*[])
{

	srand(time(NULL));

	Game game;
	game.init();
	return 0;
}
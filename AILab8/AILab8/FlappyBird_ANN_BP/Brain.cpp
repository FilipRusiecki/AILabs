#include "Brain.h"
#include <iostream>
#include <numeric>
#include "Game.h"

using namespace std;

Brain::Brain()
{
}

Brain::~Brain()
{
}

void Brain::init(int inputs, int hidden, int outputs)
{
	// 2D Dynamic array in c++
	//	int** a = new int*[rowCount];
	//	for (int i = 0; i < rowCount; ++i)
	//		a[i] = new int[colCount];

	numInputs = inputs;
	numHidden = hidden;
	numOutputs = outputs;

	weightsLayer1 = new float*[inputs];
	for (int i = 0; i < inputs; i++)
		weightsLayer1[i] = new float[hidden];
	
	// Initialse weights for first layer to random values between -1 and 1.
	for (int i = 0; i < inputs; i++)
	{
		for (int j = 0; j < hidden; j++)
		{
			float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2))) - 1;
			weightsLayer1[i][j] = r;
//			std::cout << "weights layer 1 " << i << ", " << j << " = " << this->weightsLayer1[i][j]<< std::endl;
		}
	}

	weightsLayer2 = new float[hidden];

	// Initialse weights for second layer to random values between -1 and 1.
	for (int i = 0; i < hidden; i++)
	{
		float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2))) - 1;
		weightsLayer2[i] = r;
//			std::cout << "weights layer 2 " << i << " = " << this->weightsLayer2[i] << std::endl;
	}
	// Since we have only one hidden layer and one output neuron, a simple array will do it.
	// We will use the last value as the bias for the ouput neuron.
	biases = new float[hidden+1];

	for (int j = 0; j < hidden+1; j++)
	{
		float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2))) - 1;
		biases[j] = r;
//		std::cout << "Bias weights hidden layer: " << j << " = " << biases[j] << std::endl;
	}
}

// Evaluate inputs on the network
// The 5 inputs to the Flappy Bird Neural Network are :
// 1. X – coordinate of the front – most “pillar”.
// 2. Y – Coordinate of the lower part of the Upper “Pillar” i.e., (0 + height of Upper pillar)
// 3. Y – Coordinate of the upper part of the Lower “Pillar”
// 4. X – Coordinate of the Bird / Species itself
// 5. y – Coordinate of the Bird / Species itself

int Brain::FeedForward(float inputs[])
{
	float output = 0.0;
	float result = 0.0;
	int layer = 0;

	float dot[5] = { 0.0 };
	float soft[5] = { 0.0 };
	float product = 0.0;

	// Apply weights to inputs for the hidden layer
	for (int i = 0; i < numHidden; i++)
	{
		product = 0.0;
		for (int j = 0; j < numInputs; j++)
		{
			product = inputs[j] * weightsLayer1[j][i];
			dot[i] += product;
		}
//		std::cout << "result of FF. Hidden node " << i << " = " << dot[i] << std::endl;
		if (useBiases)
			dot[i] += biases[i];

		soft[i] = ReLu(dot[i]);
	}
	//Softmax typically only needed for multiclass categorisation.
//	SoftMax(soft, numHidden);

	// Apply weights to hidden layer for the output layer
	product = 0.0;
	for (int i = 0; i < numHidden; i++)
	{
		product = soft[i] * weightsLayer2[i];
		output += product;
	}
	
	if (useBiases)
		output += biases[4];

	output = Sigmoid(output);
//	std::cout << "result of sigmoid activation: " << output << std::endl;

	if (output > 0.5)
		return 1;
	else
		return 0;
}

// ReLU activation Function
float Brain::ReLu(float val)
{
		if (val < 0) val = 0;
		return val;
}

// Softmax or averaging the value
void Brain::SoftMax(float data[], int len)
{
	float sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum = sum + data[i];
	}
	if (sum == 0) sum = 1;
	for (int i = 0; i < len; i++)
	{
		data[i] = data[i] / sum;
//		std::cout << "result of softmax for node " << i << " = " << data[i] << std::endl;
	}

}

// Sigmoid Activation Function
float Brain::Sigmoid(float z)
{
	return 1.0 / (1.0 + exp(-z));
	
}


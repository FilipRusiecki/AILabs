# Based on:
# https://machinelearningmastery.com/tutorial-first-neural-network-python-keras/

# Dr. Oisin Cawley March 2021
# Using the training data from Flappy Bird we will use Tensorflow to generate the weights for our Bird's neural network-python-keras.
# I am using Anaconda Python version 3.7.4 with tensorflow 2.1.0
# Feb 2022: Tested with Python version 3.8.8 with tensorflow 2.3.0. 
#		-> Modified line 43

import numpy as np
from numpy import loadtxt
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# load the dataset
# The 5 inputs to the Flappy Bird Neural Network are :
# 1. X – coordinate of the front – most “pillar”.
# 2. Y – Coordinate of the lower part of the Upper “Pillar” i.e., (0 + height of Upper pillar)
# 3. Y – Coordinate of the upper part of the Lower “Pillar”
# 4. X – Coordinate of the Bird / Species itself
# 5. y – Coordinate of the Bird / Species itself

dataset = loadtxt('training_data.csv', delimiter=',')
# split into input (X) and output (y) variables
X = dataset[:,0:5]
y = dataset[:,5]

# define the keras model. This must be the same as the structure we will use in Flappy Brid's brain.
model = Sequential()
model.add(Dense(4, input_dim=5, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

# compile the keras model
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

# fit the keras model on the dataset
model.fit(X, y, epochs=30, batch_size=100)	# Try playing with these hyperparameters to see what the effect is.

# evaluate the keras model
_, accuracy = model.evaluate(X, y)
print('Accuracy: %.2f' % (accuracy*100))

# make some class predictions with the model as a demonstration
#predictions = model.predict_classes(X) --Deprecated
predictions = np.argmax(model.predict(X), axis=-1)
# summarize the first 15 cases
for i in range(15):
	print('%s => %d (expected %d)' % (X[i].tolist(), predictions[i], y[i]))
	
# save model and architecture to single file
model.save("flappy_model.h5")

# We can also save the architecture and weights separately if we want
# serialize model to JSON
#model_json = model.to_json()
#with open("model_weights.json", "w") as json_file:
#    json_file.write(model_json)
# serialize weights to HDF5
#model.save_weights("model.h5")

print("Saved model to disk")

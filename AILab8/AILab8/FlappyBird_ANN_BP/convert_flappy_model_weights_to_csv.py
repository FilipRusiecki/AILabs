# Dr. Oisin Cawley March 2021
# Load the keras model and write the weights out to a txt file
# We will read the txt file back into flappy bird's brain

from tensorflow.keras.models import load_model
import numpy
import os
import csv

# load model
loaded_model = load_model('flappy_model.h5')
# summarize model.
loaded_model.summary()

print("Loaded model from disk")

index=0
with open('flappy_tf_weights.csv', mode='w') as weights_file:
    weights_writer = csv.writer(weights_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    for layer in loaded_model.layers:
        weights = layer.get_weights() # list of numpy arrays
        print("Layer %d" %index)
        print("Layer name %s" %layer.name)
        print(weights)
        for item in weights:   
            for item2 in item:   
                weights_writer.writerow(item2.flatten())
        index = index+1


# Boids

This project attempts to simulate flocking behavior, through the creation of simple entities called Boids (birdoids). These boids, which exist on a two-dimensional plane, function through three simple rules -- alignment, cohesion, and separation.

Alignment causes boids to match velocity of nearby boids.
Cohesion causes boids to seek the center of mass of the nearest clump of boids.
Separation prevents boids from getting too close to each other. 

These three simple rules cause complex behavior to emerge, which is what makes the boid simulation interesting. The algorithms were originally formulated by Craig Reynolds in the 1980s.

Currently, the simulation runs on Windows, through Visual Studio. Appropriate libraries must be linked -- we utilized SFML (Simple Fast Multimedia Library) to visualize the project. Instructions on how to do this through Visual Studio can be found at http://www.sfml-dev.org/tutorials/2.2/start-vc.php

Also, the project is able to run on Ubuntu and Debian-based distributions. To install the necessary libraries, run
```
sudo apt-get install libsfml-dev
```
Further information on using SFML with Linux can be found at http://www.sfml-dev.org/tutorials/2.2/start-linux.php

### How to clone this repository while using Visual Studio ###
* Open up Visual Studio
* "Open from Source Control"
* Input the cloning link from Github repo
* Visual Studio might prompt you to install Git GUI. Do so. Once that's done, you should see the solution "Boids" on the left side. Double click it and you should be good to go.
To commit saved changes to the bitbucket repo, open up Git GUI and open up the Boids folder. From there you commit. Then when you want to push up to the Github repo, you click push.

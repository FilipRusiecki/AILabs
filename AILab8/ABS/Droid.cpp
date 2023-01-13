#include "Droid.h"
#include "MoveAway.h"
#include <string>
#include <iostream>
using namespace std;

Droid::Droid(string name, int x, int y, int health, int damage, Grid& grid)
{
    this->name = name;
    this->x = x;
    this->y = y;
//    this->range = range;
    this->damage = damage;
    this->health = health;
    position = grid.getGridLocation(x, y);
    target = position;

    if (!droidTex.loadFromFile("ASSETS\\IMAGES\\BB-8.png"))
    {
        // simple error message if previous call fails
        std::cout << "problem loading sprite" << std::endl;
    }
    sf::Vector2u z = droidTex.getSize();
    droidSprite.setTexture(droidTex);
    droidSprite.setScale(sf::Vector2f(0.002f * grid.nodes[0][0].s_radius, 0.002f * grid.nodes[0][0].s_radius));
    droidSprite.setOrigin(z.x / 2, z.y / 2);
    //droidSprite.setPosition((x, y));

}

void Droid::update(Grid& grid)
{
    if (!isAlive())
    {
        std::cout << name + " is dead! " << std::endl;
        return;
    }
    droidSprite.setPosition(position);
    x = grid.getGridCellX(sf::Vector2i(position));
    y = grid.getGridCellY(sf::Vector2i(position));
        
    if (health > 0)
        health = health - 0.1;

    // We use the brain behaviour as a sort of master controller.
    // The brain behaviour always runs first and checks to see have any alarm conditions arisen while the BT has been executing.
    // If so we will have specific code here to handle them. We will also set a flag so that the current behaviour executing in the BT will make itself Fail,
    // thereby forcing a re-evaluation of the BT from the root.
    // This is only necessary for those behaviours that take time to run e.g. MoveTo, GetHealth
    if (brain->getState() == behaviour->RoutineState::None)
    {
        // hasn't started yet so we start it
        brain->start(". This is the Brain node for " + name);
    }
    brain->act(this, grid);
    if (brain->isSuccess()) // Success means some alarm condition has been found.
    {
        // Handle the specific alarm
        // For now it is simply to execute the first step in a MoveAway behaviour.
        // The normal Behaviour tree will Fail() due to the danger variable being set within the brain behaviour.
        if (isLowHealth())
        {
            // Specific actions for lowHealth alarm
        }
        else
        {
            // Specific actions for enemy nearby
            MoveAway moveAway = MoveAway(3, grid);
            moveAway.start(" as Alarm for " + name);
            moveAway.act(this, grid);
        }
    }
    // Now run the main BT
    if (behaviour->getState() == behaviour->RoutineState::None)
    {
        // hasn't started yet so we start it
        behaviour->start(" for " + name);
    }
    behaviour->act(this, grid);

    handleCollisions(grid);
    brain->reset(" from the Droid update.");    //We want this to run every time.
}

float Droid::getNewOrientation(Grid& grid) {
    sf::Vector2f direction = target - position;
    if (grid.length(direction) > 0) 
    {
        float rads = atan2(direction.y, direction.x);
        float newAngle = rads * 180 / pi;   // Convert to degrees
        return newAngle + 90;	            // Becasue SFML orientation has 0 degrees pointing up, while normal trigonometry has 0 along the x axis.
    }
    else
        return 0;
}

bool Droid::isAlive()
{
    return health > 0;
}

void Droid::draw(sf::RenderWindow& t_window, Grid& grid)
{
    if (!isAlive())
    {
        droidSprite.setColor(sf::Color::Black);
    }
    else if (danger)     // For the case where we are in proximity of danger.
    {
        droidSprite.setColor(sf::Color::Red);
        //danger = false;       // This should be set specifically by a behaviour
    }
    else if (alarmHasBeenRaised && !isLowHealth())
        droidSprite.setColor(sf::Color::Green);
    else if (isLowHealth())
            droidSprite.setColor(sf::Color::Cyan);
    //else
        //droidSprite.setColor(sf::Color::White);

    t_window.draw(droidSprite); //Position of sprite set by the MoveTo behaviour
}

Routine* Droid::getBehaviour() {
    return behaviour;
}

void Droid::setBehaviour(Routine* routine) {
    this->behaviour = routine;
}

Routine* Droid::getBrain() {
    return brain;
}

void Droid::setBrain(Routine* routine) {
    this->brain = routine;
}

//Normalise a vector
sf::Vector2f Droid::normalize(const sf::Vector2f source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

bool Droid::isLowHealth()
{
    return (health < lowHealth);
}

void Droid::addHealth(int newHealth)
{
    health += newHealth;
    std::cout << name + " has picked up some extra health. Value " << newHealth << std::endl;

}

void Droid::handleCollisions(Grid& grid)
{
    for (HealthPill* hp : grid.m_gridHealthPills)
    {
        if (hp->visible)
        {
            sf::Vector2f direction = grid.getGridLocation(hp->x, hp->y) - position;
            if ((int)grid.length(direction) == 0)
            {
                hp->HasBeenPickedUp();
                addHealth(hp->strength);
            }
        }
    }
}


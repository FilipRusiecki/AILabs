//#pragma once
#ifndef DROID_H
#define DROID_H

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Routine.h"
#include "HealthPill.h"
#include <string>

using namespace std;

static const float pi = 3.141592654f;

class Droid
{
public:

    string name;
    int x;
    int y;
//    int range;
    int damage;
    float health;
    int lowHealth = 40;
    bool danger = false;                //Set inside the CheckForAlarms Behaviour
    bool alarmHasBeenRaised = false;    //Set inside the CheckForAlarms Behaviour
    sf::Vector2f position;
    sf::Vector2f target;
    sf::Vector2f velocity;

    Routine* brain;
    Routine* behaviour;
    
    // An ID for the droid, its start grid location, how much health ti starts with, how much damage it starts with, the Grid
    Droid(string name, int x, int y, int health, int damage, Grid& grid);
    void update(Grid& grid);
    void draw(sf::RenderWindow& t_window, Grid& grid);
    bool isAlive();
    bool isLowHealth();
    void addHealth(int newHealth);
    float getNewOrientation(Grid& grid);
    void handleCollisions(Grid& grid);

    Routine* getBehaviour();
    void setBehaviour(Routine* routine);
    Routine* getBrain();
    void setBrain(Routine* routine);
    sf::Vector2f normalize(const sf::Vector2f source);

//    sf::Sprite objSprite;
    sf::Texture droidTex;
    sf::Sprite droidSprite;

};
#endif
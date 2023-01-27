#ifndef HEALTH_H
#define HEALTH_H

#include <SFML/Graphics.hpp>
#include "Grid.h"

//class Grid;

class HealthPill
{
public:

    int x;
    int y;
    int strength;
    sf::Vector2f position;
    bool visible = false;

    HealthPill(int x, int y, int strength, bool visible, Grid& grid);
    void update(Grid& grid);
    void draw(sf::RenderWindow& t_window, Grid& grid);
    void HasBeenPickedUp();

    sf::Texture healthTex;
    sf::Sprite healthSprite;

};
#endif
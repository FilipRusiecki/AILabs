#include "HealthPill.h"
#include <iostream>
using namespace std;

HealthPill::HealthPill(int x, int y, int strength, bool visible, Grid& grid)
{
    this->x = x;
    this->y = y;
    this->strength = strength;
    this->visible = visible;
    position = grid.getGridLocation(x, y);

    if (!healthTex.loadFromFile("ASSETS\\IMAGES\\Health.png"))
    {
        // simple error message if previous call fails
        std::cout << "problem loading sprite" << std::endl;
    }
    sf::Vector2u z = healthTex.getSize();
    healthSprite.setTexture(healthTex);
    healthSprite.setScale(sf::Vector2f(0.002f * grid.nodes[0][0].s_radius, 0.002f * grid.nodes[0][0].s_radius));
    healthSprite.setOrigin(z.x / 2, z.y / 2);
    healthSprite.setPosition(position);

}

void HealthPill::update(Grid& grid)
{
}

void HealthPill::draw(sf::RenderWindow& t_window, Grid& grid)
{
    if (visible)     // For the case where we are in proximity of danger.
    {
        t_window.draw(healthSprite); //Position of sprite set by the MoveTo behaviour
    }
}

void HealthPill::HasBeenPickedUp()
{
    visible = false;
}
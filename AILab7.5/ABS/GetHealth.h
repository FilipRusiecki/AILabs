#ifndef GETHEALTH_H
#define GETHEALTH_H

#include "Droid.h"
#include "Routine.h"
#include <iostream>
#include <cmath>        // std::abs

// MoveAway from what? That is the question for this behaviour.
// Since this version does not take any parameters it is free to figure out itself what it should move away from.
// We could have new behaviour called IfDroidInRangeMoveAway, and then we could combine the two behaviours into a new one.
class GetHealth : public Routine
{

public:

    int destX;
    int destY;
    sf::Vector2f target;

    GetHealth(Grid& g) : Routine()    // Superclass constructor
    {
        this->destX = 1;
        this->destY = 1;
        this->target = g.getGridLocation(destX, destY);
        this->routineType = "GetHealth";
        this->routineGrid = &g;
    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid)
    {
        if (isRunning())
        {
            if (!droid->isAlive())
            {
                fail();
                return;
            }

            bool healthFound = false;
            int closest = 100000;
            int healthX = 0;
            int healthY = 0;
            HealthPill* tempHP = NULL; // Want to temporarily remember which HP we are heading to.

            for (HealthPill* hp : grid.m_gridHealthPills)
            {
                int d = 0;
                if (hp->visible) 
                {
                    healthFound = true;
                    d = distance(droid->x, droid->y, hp->x, hp->y);
                    if (d < closest)
                    {
                        tempHP = hp;
                        closest = d;
                        healthX = hp->x;
                        healthY = hp->y;
                    }
                }
            }
            if (healthFound)
            {
                // Move one grid cell directly towards the HealthPill
                if (healthX > droid->x)
                    destX = droid->x + 1;
                else if (healthX < droid->x)
                    destX = droid->x - 1;
                if (healthY > droid->y)
                    destY = droid->y + 1;
                else if (healthY < droid->y)
                    destY = droid->y - 1;
                if (destX <= 0) destX = 1;
                if (destY <= 0) destY = 1;
                if (destX > grid.gridSize)
                    destX = grid.gridSize;
                if (destY > grid.gridSize)
                    destY = grid.gridSize;
            }
            else    // No HealthPills around
            {
                fail();
                return;
            }

            droid->target = grid.getGridLocation(destX, destY);     // A bit of cludge so we can move the droid smoothly

            if (!isDroidAtDestination(droid, grid))
            {
                moveDroid(droid, grid);
                if (isDroidAtDestination(droid, grid)) // Check again following the last move
                {
                    tempHP->HasBeenPickedUp();
                    droid->addHealth(tempHP->strength);
                    succeed("GetHealth for " + droid->name);
                }
            }
            else    // Should never get here.
            {
                tempHP->HasBeenPickedUp();
                droid->addHealth(tempHP->strength);
                succeed("GetHealth for " + droid->name);
            }
        }
    }

    void moveDroid(Droid* droid, Grid& grid)
    {
        int steps = 1;
        sf::Vector2f direction = droid->target - droid->position;
        if (std::abs(grid.length(direction)) > 0)
        {
            if (droid->target.y != droid->position.y)
            {
                if (droid->target.y > droid->position.y)
                {
                    droid->position.y = droid->position.y + steps;
                }
                else {
                    droid->position.y = droid->position.y - steps;
                }
            }
            if (droid->target.x != droid->position.x)
            {
                if (droid->target.x > droid->position.x)
                {
                    droid->position.x = droid->position.x + steps;
                }
                else {
                    droid->position.x = droid->position.x - steps;
                }
            }
        }
        std::cout << ">>> Droid " << droid->name << " moving to (HealthPill):  " << destX << ", " << destY << std::endl;
        std::cout << ">>> position: (" << droid->position.x <<", " << droid->position.y << ")" << " target: (" << droid->target.x <<", " << droid->target.y << ")" << std::endl;
    }

    bool isDroidAtDestination(Droid* droid, Grid& grid)
    {
        sf::Vector2f direction = droid->target - droid->position;
        //        int l = (int) grid.length(direction);
        return ((int)grid.length(direction) == 0);
    }

    int distance(int dx, int dy, int hx, int hy)
    {
        return (abs(dx - hx) + abs(dy - hy));       // Checking distance in terms of Grid squares not pixels.
    }

};
#endif

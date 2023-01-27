#ifndef MOVETO_H
#define MOVETO_H

#include "Droid.h"
#include "Routine.h"
#include <iostream>
#include <cmath>        // std::abs

class MoveTo : public Routine 
{

public:

    int destX;
    int destY;
    sf::Vector2f target;

    MoveTo(int destX, int destY, Grid& g) : Routine()    // Superclass constructor
    {
        this->destX = destX;
        this->destY = destY;
        this->target = g.getGridLocation(destX, destY);
        this->routineType = "MoveTo";
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
            if (!droid->isAlive() || droid->alarmHasBeenRaised)
            {
                fail();
                return;
            }
            droid->target = grid.getGridLocation(destX, destY);     // A bit of cludge so we can move the droid smoothly
            if (!isDroidAtDestination(droid, grid)) {
                moveDroid(droid, grid);
            }
            else
                succeed("MoveTo for " + droid->name);               // This is the case when we ask it to move to its current location

        }
    }

    void moveDroid(Droid* droid, Grid& grid)
    {
        std::cout << ">>> Droid " << droid->name << " moving to " << destX << ", " << destY << std::endl;

        sf::Vector2f direction = droid->target - droid->position;
        if (std::abs(grid.length(direction)) > 0)
        {
            if (droid->target.y != droid->position.y)
            {
                if (droid->target.y > droid->position.y)
                {
                    droid->position.y = droid->position.y + 1;
                }
                else {
                    droid->position.y = droid->position.y - 1;
                }
            }
            if (droid->target.x != droid->position.x)
            {
                if (droid->target.x > droid->position.x)
                {
                    droid->position.x = droid->position.x + 1;
                }
                else {
                    droid->position.x = droid->position.x - 1;
                }
            }
        }
//        std::cout << ">>> Droid " << droid->name << " moving to:  " << destX << ", " << destY << std::endl;
        if (isDroidAtDestination(droid, grid)) {
            succeed("MoveTo for " + droid->name);
        }
    }

    bool isDroidAtDestination(Droid* droid, Grid& grid)
    {
        sf::Vector2f direction = droid->target - droid->position;
//        int l = (int) grid.length(direction);
        return ((int)grid.length(direction) == 0);
    }
};
#endif

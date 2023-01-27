#ifndef MOVEAWAY_H
#define MOVEAWAY_H

#include "Droid.h"
#include "Routine.h"
#include <iostream>
#include <cmath>        // std::abs

// MoveAway from what? That is the question for this behaviour.
// Since this version does not take any parameters it is free to figure out itself what it should move away from.
// We could have new behaviour called IfDroidInRangeMoveAway, and then we could combine the two behaviours into a new one.
class MoveAway : public Routine
{

public:

    int range;
    int destX;
    int destY;
    sf::Vector2f target;

    MoveAway(int range, Grid& g) : Routine()    // Superclass constructor
    {
        this->range = range;
        this->destX = 1;
        this->destY = 1;
        this->target = g.getGridLocation(destX, destY);
        this->routineType = "MoveAway";
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
            // Find any droid in range, checking all droids
            bool isDanger = false;
            for (Droid* enemy : grid.m_gridDroids)
            {
                {
                    if (droid != enemy)     // Check we are not looking at ourselves.
                    {
                        if (isInRange(droid, enemy))
                        {
                            isDanger = true;
                            // Move one grid cell directly away from the enemy
                            if (enemy->x >= droid->x)
                                destX = droid->x - 1;
                            else
                                destX = droid->x + 1;
                            if (enemy->y >= droid->y) 
                                destY = droid->y - 1;
                            else
                                destY = droid->y + 1;
                            if (destX <= 0) destX = 1;
                            if (destY <= 0) destY = 1;
                            // Check for getting stuck in corners
                            if (destX == 1 && destY == 1)
                            {
                                if (enemy->x >= droid->x)
                                    destY = 3;
                                else
                                    destX = 3;
                            }
                            if (destX > grid.gridSize) 
                                destX = grid.gridSize;
                            if (destY > grid.gridSize) 
                                destY = grid.gridSize;
                            // Check for getting stuck in corners
                            if (destX == grid.gridSize && destY == grid.gridSize)
                            {
                                if (enemy->x >= droid->x)
                                    destY = grid.gridSize-3;
                                else
                                    destX = grid.gridSize-3;
                            }
                            break;  // Just react to the first Droid we find in range.
                        }
                    }
                }
            }
            if (!isDanger)  // No enemies found to move away from
            {
                droid->danger = false;
                succeed("MoveAway for " + droid->name + " but no enemies near.");
                return;
            }
            droid->target = grid.getGridLocation(destX, destY);     // A bit of cludge so we can move the droid smoothly
            // Need the below since the droid may not be in danger by the time the MoveAway behaviour finishes or while it is running.

            if (!isDroidAtDestination(droid, grid)) 
            {                    
                moveDroid(droid, grid);
            }
            else
                succeed("MoveAway for " + droid->name);
        }
    }

    void moveDroid(Droid* droid, Grid& grid)
    {
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

        std::cout << ">>> Droid " << droid->name << " moving AWAY to:  " << destX << ", " << destY << std::endl;

        if (isDroidAtDestination(droid, grid)) {
            succeed("MoveAway for " + droid->name);
        }
    }

    bool isDroidAtDestination(Droid* droid, Grid& grid)
    {
        sf::Vector2f direction = droid->target - droid->position;
        //        int l = (int) grid.length(direction);
        return ((int)grid.length(direction) == 0);
    }

    bool isInRange(Droid* droid, Droid* enemy)
    {
        return (abs(droid->x - enemy->x) <= range
            && abs(droid->y - enemy->y) <= range);       // Checking distance in terms of Grid squares not pixels.
    }

};
#endif

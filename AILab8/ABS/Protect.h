#ifndef PROTECT_H
#define PROTECT_H

#include "Droid.h"
#include "Routine.h"
#include <iostream>
#include <cmath>        // std::abs

//
// This behaviour tries to position itself so that droidB is located between it and droiA.
// In effect it Protects from A behind B.
// If we pass in (-1, -1_ as the droid numbers it will pick 2 other droids at random for A and B.
//
class Protect : public Routine
{

public:

    int destX;
    int destY;
    sf::Vector2f target;
    int droidA;
    int droidB;

    Protect(int droidA, int droidB, Grid& g) : Routine()    // Superclass constructor
    {
        this->destX = 1;
        this->destY = 1;
        this->target = g.getGridLocation(destX, destY);
        this->routineType = "Protect";
        this->routineGrid = &g;

        // If we get -1 passed in then we will self select the droids in 'Act' below, so leave it as -1.
        // Otherwise subtract 1 so we map to the correct index which starts at 0
        this->droidA = droidA;
        this->droidB = droidB;
        if (droidA != -1) this->droidA = droidA - 1;
        if (droidB != -1) this->droidB = droidB - 1;

    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid)
    {
        int droidAx;
        int droidAy;
        int droidBx;
        int droidBy;
        int distanceToProtectPoint = 2;

        // First time we enter we must set the two target droids (we assume there ar at least 3 droids in the system)
        // If the parameters are -1,-1 then self select 2 other droids
        if (droidA == -1 || droidB == -1)
        {
            // Use current time as seed for random generator
            srand(time(0));
            int r = 0;
            while (droidA == -1)
            {
                r = (rand() % (int)grid.m_gridDroids.size() - 1) + 1;
                if (grid.m_gridDroids[r] != droid)
                {
                    droidA = r;
                }
            }
            while (droidB == -1)
            {
                r = (rand() % (int)grid.m_gridDroids.size() - 1) + 1;
                if (grid.m_gridDroids[r] != droid && r != droidA)
                {
                    droidB = r;
                }
            }
        }
        if (isRunning())
        {
            if (!droid->isAlive() || droid->alarmHasBeenRaised)
            {
                fail();
                return;
            }
            droidAx = grid.m_gridDroids[droidA]->x;
            droidAy = grid.m_gridDroids[droidA]->y;
            droidBx = grid.m_gridDroids[droidB]->x;
            droidBy = grid.m_gridDroids[droidB]->y;

            // Now we need to figure out where the Protect position is.
            sf::Vector2f AB = sf::Vector2f(droidBx - droidAx, droidBy - droidAy);
            float lenAB = grid.length(AB);
            sf::Vector2f ABn = droid->normalize(AB);
                                     //what i did to make it protect is just simply swap the + to a - to invert the hide position 
            sf::Vector2f C = sf::Vector2f(droidBx - ABn.x * distanceToProtectPoint, droidBy - ABn.y * distanceToProtectPoint); // C is the porposed Protect point
            // Next we need to think about whether there is a closer hiding point to us if we are further away.
            // If we get the dot product of the two vectors A->B and A->D(our current position) we will have our projected length on to AB
            // Adding this to the coordinates of A will give us the projected point X on AB
            // If this length (AX) is less than AC then goto C othewise goto X
                                     //what i did to make it protect is just simply swap the - to a + to invert the hide position (same with this line but changed the - to a +)
            float lenAC = grid.length(sf::Vector2f(C.x + droidAx, C.y + droidAy));
            sf::Vector2f AD = sf::Vector2f(droid->x - droidAx, droid->y - droidAy);
            float AX = (AD.x * AB.x + AD.y * AB.y) / lenAB; // Get the dot product which returns a scalar value
            sf::Vector2f X = sf::Vector2f(ABn.x * AX + droidAx, ABn.y * AX + droidAy); // X is the intersection point on AB
            float lenAX = grid.length(sf::Vector2f(X.x - droidAx, X.y - droidAy));
            if (lenAX < lenAC)
            {
                destX = round(C.x);
                destY = round(C.y);
            }
            else
            {
                destX = round(X.x);
                destY = round(X.y);
            }
            if (destX < 1) destX = 1;
            if (destY < 1) destY = 1;
            if (destX > grid.gridSize) destX = grid.gridSize;
            if (destY > grid.gridSize) destY = grid.gridSize;

            droid->target = grid.getGridLocation(destX, destY);     // A bit of cludge so we can move the droid smoothly
            if (!isDroidAtDestination(droid, grid)) {
                moveDroid(droid, grid);
            }
            else
                succeed("Protect for " + droid->name);               // This is the case when we ask it to move to its current location

        }
    }

    void moveDroid(Droid* droid, Grid& grid)
    {
        std::cout << ">>> Droid " << droid->name << " moving to " << destX << ", " << destY << std::endl;
        // Check are we going out of the Grid
        if (destX < 1 || destX > grid.gridSize || destY < 1 || destY > grid.gridSize)
            return;
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

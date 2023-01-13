#include "Routine.h"
#include "Droid.h"

class IsDroidInRange : public Routine
{

public:
    int range;

    IsDroidInRange(int range) {
        this->range = range;
        routineType = "IsDroidInRange";
    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid)
    {
        // Find any droid in range
        // Checking all droids
        droid->danger = false;
        for (Droid* enemy : grid.m_gridDroids)
        {
            {
                if (droid != enemy)     // Check we are not looking at ourselves.
                {
                    if (enemy->isAlive() && isInRange(droid, enemy))
                    {
                        succeed("IsDroidInRange " + enemy->name + " is in range of " + droid->name);
                        droid->danger = true;
                        return;
                    }
                }
            }
        }
        fail();
    }

    bool isInRange(Droid* droid, Droid* enemy)
    {
        return (abs(droid->x - enemy->x) <= range
            && abs(droid->y - enemy->y) <= range);       // Checking distance in terms of Grid squares not pixels.
    }
};
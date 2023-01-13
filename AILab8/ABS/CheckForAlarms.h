#include "Routine.h"
#include "Droid.h"

class CheckForAlarms : public Routine
{

public:
    CheckForAlarms() {
        routineType = "CheckForAlarms";
    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid)
    {
        if (!isRunning()) {
            return;
        }

        // Find any droid in range
        // Checking all droids
        droid->danger = false;
        droid->alarmHasBeenRaised = false;
        for (Droid* enemy : grid.m_gridDroids)
        {
            {
                if (droid != enemy)     // Check we are not looking at ourselves.
                {
                    if (enemy->isAlive() && isInRange(droid, enemy))
                    {
                        succeed("CheckForAlarms " + enemy->name + " is in range of " + droid->name);
                        droid->danger = true;
                        droid->alarmHasBeenRaised = true;
                        return;
                    }
                }
            }
        }
        // Check health status
        if (droid->isLowHealth())
        {
            succeed("CheckForAlarms " + droid->name + " health below 40%.");
            droid->alarmHasBeenRaised = true;
            return;
        }
        fail();
    }

    bool isInRange(Droid* droid, Droid* enemy)
    {
        return (abs(droid->x - enemy->x) <= 3   //Hard coding 3 in here becasue I am changin the way the range is handled for the droid. Will fix this later.
            && abs(droid->y - enemy->y) <= 3);       // Checking distance in terms of Grid squares not pixels.
    }
};
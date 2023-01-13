#include "Droid.h"
#include "MoveTo.h"
#include <iostream>

class Repeat : public Routine 
{

public:

    Routine* routine;
    int times;
    int originalTimes;

    // Will repeat the given routine until it Fails.
    Repeat(Routine* routineToRepeat) : Routine()    // Superclass constructor
    {
        routine = routineToRepeat;
        times = -1; // infinite
        originalTimes = times;
        routineType = "Repeat";
    }

    // Will repeat the given routine until it Fails or the number of repititions has been reached.
    Repeat(Routine* routineToRepeat, int timesToRepeat) : Routine()    // Superclass constructor
    {
        this->routine = routineToRepeat;
        if (timesToRepeat < 1) 
        {
            std::cout << ">>> Repeat Routine failed. Can't repeat a routine negative times." << std::endl;
            fail();
        }
        times = timesToRepeat;
        originalTimes = times;
        routineType = "Repeat";
    }

    void start(string msg)
    {
        std::cout << ">>> Starting routine " << routineType << msg << std::endl;
        state = RoutineState::Running;
        routine->start(" from a Repeat node.");
    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        times = originalTimes;
        routine->reset(" from a Repeat node");
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid)
    {
        if (!isRunning()) {
            return;
        }
        if (routine->isRunning()) {
            routine->act(droid, grid);
        }
        else if (routine->isFailure())
        {
            fail();       // In this case the Repeat node will also fail when the child fails, and will not Repeat anymore.
        }
        else if (routine->isSuccess()) 
        {
            if (times == 0) {
                succeed("Repeat for " + droid->name);
                return;
            }
            if (times > 0 || times <= -1) {
                times--;
                routine->reset(" from a Repeat node. Repeating " + std::to_string(times) + " more times.");
                routine->start(" from a Repeat node.");
            }
        }
    }
};
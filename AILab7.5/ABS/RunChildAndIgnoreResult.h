#include "Droid.h"
#include "MoveTo.h"
#include <iostream>

// This Decorator node will simple run the sub-behaviour and continue to the next node regardless.
// The thinking here is that we could use this as a mechanism to inspect the environment to handle "alarm" conditions
// i.e. game conditions which would require current Running behaviours to abort or pause.
class RunChildAndIgnoreResult : public Routine
{

public:

    Routine* routine;
    int times;
    int originalTimes;

    // Will repeat the given routine until it Fails.
    RunChildAndIgnoreResult(Routine* routineToRepeat) : Routine()    // Superclass constructor
    {
        routine = routineToRepeat;
        times = -1; // infinite
        originalTimes = times;
        routineType = "RunChildAndIgnoreResult";
    }

    void start(string msg)
    {
        std::cout << ">>> Starting routine " << routineType << msg << std::endl;
        state = RoutineState::Running;
        routine->start(" from a RunChildAndIgnoreResult node.");
    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        times = originalTimes;
        routine->reset(" from a RunChildAndIgnoreResult node");
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
        else // We don't care if it succeeded or failed.
        {
            succeed("RunChildAndIgnoreResult for " + droid->name);
        }
    }
};
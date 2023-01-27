#include "Droid.h"
#include "MoveTo.h"
#include <iostream>

class Wander : public Routine {

public:

    MoveTo* moveTo;

    Wander(Grid& grid) : Routine()    // Call Superclass constructor with no arguments
    {
        srand(time(0));
        moveTo = new MoveTo(rand() % grid.gridSize + 1, rand() %grid.gridSize + 1, grid);
        this->routineType = "Wander";
        this->routineGrid = &grid;

    }

    void start(string msg)
    {
        std::cout << ">>> Starting routine " << routineType << msg << std::endl;
        state = RoutineState::Running;
        moveTo->start(" from a Wander node.");
    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        moveTo = new MoveTo(rand() % routineGrid->gridSize + 1, rand() % routineGrid->gridSize + 1, *routineGrid);
        moveTo->reset(" from a Wander node");
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid) 
    {
        if (!moveTo->isRunning()) 
        {
            return;
        }
        moveTo->act(droid, grid);
        if (moveTo->isSuccess()) {
            succeed("Wander for " + droid->name);
        }
        else if (moveTo->isFailure()) {
            fail();
        }
    }
};
#include "Droid.h"
#include "MoveTo.h"
#include <iostream>
#include <list> 
#include <iterator> 
#include <queue> 

class Selector : public Routine
{

public:
    Selector()
    {
        routineType = "Selector";
    }

    Routine* currentRoutine;
    list<Routine*> routines; 
    queue<Routine*> routineQueue;


    void addRoutine(Routine* routine) {
        routines.push_back(routine);
    }

    void reset(string msg) {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        state = RoutineState::None;
//        start(" resetting.");
        for (Routine* routine : routines) {
            routine->reset(" from a Selector node.");
        }
    }

    void start(string msg)
    {
        // Start the current sequence
        // Reset the current queue and copy the routines from setup
        std::cout << ">>> Starting routine " << routineType << msg << std::endl;
        clearQueue(routineQueue);
        addRoutinesToQueue(routines, routineQueue);
        currentRoutine = routineQueue.front();
        routineQueue.pop();
        state = RoutineState::Running;
        currentRoutine->start(" from a Selector node.");
    }

    void clearQueue(std::queue<Routine*>& q)
    {
        std::queue<Routine*> empty;
        std::swap(q, empty);
    }

    void addRoutinesToQueue(list<Routine*>& r, std::queue<Routine*>& q)
    {
        for (Routine* routine : r) {
            q.push(routine);
        }
    }

    void act(Droid* droid, Grid& grid)
    {
        if (!isRunning()) {
            return;
        }
        currentRoutine->act(droid, grid);
        // if is still running, then carry on
        if (currentRoutine->isRunning())
        {
            return;
        }
        // Check if any sub-behaviour was successful and if so finish the selection
        if (currentRoutine->isSuccess()) {
            succeed("Selector for " + droid->name);
            return;
        }

        // Sub-behaviour failed, so we need to progress the selection. 
        // If there are no more routines then the state is the last routine's state
        if (routineQueue.empty()) {
            // We processed the last routine in the sequence so set the state to that (which should be Failed if we get this far)
            state = currentRoutine->getState();
            // check if the routine is successful and finish the sequence
            if (currentRoutine->isFailure()) {
                fail();
                return;         
            }
        }
        else {
            currentRoutine = routineQueue.front();
            routineQueue.pop();
            currentRoutine->start(" from a Selector node.");
        }
    }
};

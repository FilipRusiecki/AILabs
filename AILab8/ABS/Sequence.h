#include "Droid.h"
#include "MoveTo.h"
#include <iostream>
#include <list> 
#include <iterator> 
#include <queue> 

class Sequence : public Routine
{

public:
    Sequence()
    {
        routineType = "Sequence";
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
        for (Routine* routine : routines)
            routine->reset(" from a Sequence node");
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
        currentRoutine->start(" from a Sequence node.");
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
        else if (currentRoutine->isFailure())       // If any sub-behaviour fails then we exit the Sequence
        {
            fail();
            return;
        }

        // We need to progress the sequence. If there are no more routines
        // then the state is the last routine's state.
        if (routineQueue.empty()) {
            if (currentRoutine->isSuccess())
                succeed("Sequence for " + droid->name);
            else if (currentRoutine->isFailure())
                fail();
            return;
        }
        else {
            currentRoutine = routineQueue.front();
            routineQueue.pop();
            currentRoutine->start(" from a Sequence node.");
        }

    }
};

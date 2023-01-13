#ifndef ROUTINE_H
#define ROUTINE_H

#include <iostream>
//#include "Grid.h"     // Getting all sorts of issue due to circular inclusions I think.
//#include "Droid.h"    // Added the forward references below instead.

class Grid;
class Droid;

using namespace std;


class Routine
{

public:
    enum RoutineState
    {
        None,
        Success,
        Failure,
        Running
    };

    RoutineState state = RoutineState::None;
    string routineType = "empty";
    Grid* routineGrid;

    Routine() {};

    virtual void reset(string msg) {};

    virtual void start(string msg)
    {
        std::cout << ">>> Starting routine " << routineType << msg << std::endl;
        state = RoutineState::Running;
    };

    virtual void act(Droid* droid, Grid& grid) {};   //If you leave out the virtual, it will not perform the 
                                                     //Polymorphic call to the 'act' method. Bloody C++.

    bool isSuccess() {
        return (state == RoutineState::Success);
    };

    bool isFailure() {
        return (state == RoutineState::Failure);
    };

    bool isRunning() {
        return (state == RoutineState::Running);
    };

    RoutineState getState() {
        return state;
    };

    void succeed(string msg) {
        std::cout << ">>> Routine SUCCEEDED for " << msg << std::endl;
        state = RoutineState::Success;
    };

    void fail() {
        std::cout << ">>> Routine FAILED for " << routineType << std::endl;
        state = RoutineState::Failure;
    };

};

#endif

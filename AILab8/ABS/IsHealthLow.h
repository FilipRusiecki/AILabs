#include "Routine.h"
#include "Droid.h"

class IsHealthLow : public Routine
{
    int lowHealthValue = 50;    // Default if none specified
public:
    IsHealthLow() {
        routineType = "IsHealthLow";
    }

    IsHealthLow(int lowHealthValue) {
        routineType = "IsHealthLow";
        this->lowHealthValue = lowHealthValue;
    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid)
    {
        if (droid->isLowHealth())
        {
            succeed("IsHealthLow " + droid->name + ". Health is " + std::to_string(droid->health));
            return;
        }
        else
        {
            fail();
        }
    }

};
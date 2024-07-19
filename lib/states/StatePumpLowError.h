
#ifndef STATE_PUMP_LOW_ERROR_H
#define STATE_PUMP_LOW_ERROR_H
#include "State.h"

class StatePumpLowError : public State
{

    public:
        StatePumpLowError(StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl) :
        State(statusHandler, pressureSensor, relayControl){};

        SystemState tick() override;
        virtual void enterState() override;
    private:
        
};



#endif // STATE_PUMP_LOW_ERROR_H
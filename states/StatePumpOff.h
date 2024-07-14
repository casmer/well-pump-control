
#ifndef STATE_PUMP_OFF_H
#define STATE_PUMP_OFF_H
#include "State.h"

class StatePumpOff : public State
{

    public:
        StatePumpOff(StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl) :
        State(statusHandler, pressureSensor, relayControl){};

        SystemState tick() override;
        virtual void enter() override;
    private:
        int _lowPressureWait = 0;
    
};



#endif // STATE_PUMP_OFF_H
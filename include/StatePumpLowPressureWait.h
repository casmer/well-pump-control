
#ifndef STATE_PUMP_LOW_PRESSURE_WAIT_H
#define STATE_PUMP_LOW_PRESSURE_WAIT_H
#include <State.h>

class StatePumpLowPressureWait : public State
{
    public:
        StatePumpLowPressureWait(StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl) :
        State(statusHandler, pressureSensor, relayControl){};

        SystemState tick() override;
    protected:
        virtual void enterState() override;
};



#endif // STATE_PUMP_LOW_PRESSURE_WAIT_H

#ifndef STATE_PUMP_ON_H
#define STATE_PUMP_ON_H
#include <State.h>

class StatePumpOn : public State
{

    public:
        StatePumpOn(StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl) :
        State(statusHandler, pressureSensor, relayControl){};

        SystemState tick() override;
        virtual void enterState() override;
    private:
};



#endif // STATE_PUMP_ON_H
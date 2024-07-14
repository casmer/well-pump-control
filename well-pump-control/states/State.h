#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include "../PressureSensor.h"
#include "../RelayControl.h"
#include "../StatusHandler.h"

enum class SystemState : int
{
    PUMP_OFF = 0,
    PUMP_ON = 1,
    PUMP_LOW_PRESSURE_ERROR = 2
};

class State
{
    public:
        State( StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl):
        _statusHandler(statusHandler),
        _pressureSensor(pressureSensor),
        _relayControl(relayControl)
         {};
        virtual SystemState tick() { return SystemState::PUMP_OFF; };
        virtual void enter() { };

    protected:
    StatusHandler&  _statusHandler;
    PressureSensor& _pressureSensor;
    RelayControl&  _relayControl;

};

#endif //SYSTEM_STATE_H
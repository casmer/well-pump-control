#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include <PressureSensor.h>
#include <RelayControl.h>
#include <StatusHandler.h>

enum class SystemState : int
{
    PUMP_OFF = 0,
    PUMP_LOW_PRESSURE_WAIT = 1,
    PUMP_ON = 2,
    PUMP_LOW_PRESSURE_ERROR = 3
};

class State
{
    public:
        State( StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl):
        _statusHandler(statusHandler),
        _pressureSensor(pressureSensor),
        _pumpControl(relayControl),
        _state_entry_time(0)
         {};
        virtual SystemState tick() =0;
        void enter();
        unsigned long get_state_time_ms();
        unsigned long get_last_state_time_ms();

    protected:
        virtual void enterState() {};
        StatusHandler&  _statusHandler;
        PressureSensor& _pressureSensor;
        RelayControl&  _pumpControl;
    private:
        unsigned long _state_entry_time;
        unsigned long _last_state_time;
};

#endif //SYSTEM_STATE_H
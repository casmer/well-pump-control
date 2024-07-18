#include "states/StatePumpOn.h"
#include "PumpControlConfig.h"

SystemState StatePumpOn::tick()
{
    SystemState nextState = SystemState::PUMP_ON;

    if (_pressureSensor.getMeasuredPressure() >= CONFIG().getSetPressureHigh())
    {
        _relayControl.RelayOff();
        nextState= SystemState::PUMP_OFF;
    }
    else if ((_pressureSensor.getMeasuredPressure() <= CONFIG().getLowPressureError())
         && (get_state_time_ms() >= CONFIG().getMaxLowPressureRunTime_ms()))
    {
        _relayControl.RelayOff();
        nextState = SystemState::PUMP_LOW_PRESSURE_ERROR;
    }
    //TODO: add temperature checks to shut off on overheating conditions
    //else nothing needs to change
    
    return nextState;
};

void StatePumpOn::enterState() 
{
    _relayControl.RelayOn();
};

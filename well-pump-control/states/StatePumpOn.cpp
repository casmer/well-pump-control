#include "StatePumpOn.h"


SystemState StatePumpOn::tick()
{
    SystemState nextState = SystemState::PUMP_ON;

    if (_pressureSensor.getMeasuredPressure() >= _statusHandler.getSetPressure())
    {
        _relayControl.RelayOff();
        nextState= SystemState::PUMP_OFF;
    }
    else if ((_pressureSensor.getMeasuredPressure() <= _statusHandler.getLowPressureError())
         && (_pumpOnTime >= _statusHandler.getMaxLowPressureRunTime()))
    {
        _relayControl.RelayOff();
        nextState = SystemState::PUMP_LOW_PRESSURE_ERROR;
    }
    //TODO: add temperature checks to shut off on overheating conditions
    //else nothing needs to change
    
    _pumpOnTime++;
    return nextState;
};

void StatePumpOn::enter() 
{
    _pumpOnTime = 0;
    relayControl.RelayOn();
};

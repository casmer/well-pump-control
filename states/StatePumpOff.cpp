#include "StatePumpOff.h"


SystemState StatePumpOff::tick()
{
    SystemState nextState = SystemState::PUMP_OFF;

    if (_pressureSensor.getMeasuredPressure() <= _statusHandler.getSetPressureLow())
    {
        if (_lowPressureWait < _statusHandler.getLowPressureDelay())
        {
            _statusHandler.showMessage("Low Press wait.");
            _lowPressureWait++;
        } 
        else
        {
            nextState= SystemState::PUMP_ON;
        }
        
    }
    //else nothing needs to change
    
    return nextState;
};

void StatePumpOff::enter() 
{
    statusHandler.showMessage("Pump Off");
    _lowPressureWait=0;
};

#include "StatePumpLowError.h"


SystemState StatePumpLowError::tick()
{
    SystemState nextState = SystemState::PUMP_LOW_PRESSURE_ERROR;

    
    if (_pressureSensor.getMeasuredPressure() > _statusHandler.getLowPressureError())
    {
        _statusHandler.showMessage("Pressure Recovery");
        if (_lowPressureErrorWait > _statusHandler.getLowPressureDelay())
        {
            
            nextState= SystemState::PUMP_OFF;
        }
        _lowPressureErrorWait++;    
    }
    else
    {
        statusHandler.showMessage("Low Pressure Error");
        _lowPressureErrorWait=0;
    }
    //else nothing needs to change
    
    return nextState;
};

void StatePumpLowError::enter() 
{
    statusHandler.showMessage("Low Pressure Error");
    _lowPressureErrorWait=0;
};


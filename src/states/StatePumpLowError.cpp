#include "states/StatePumpLowError.h"
#include "PumpControlConfig.h"

SystemState StatePumpLowError::tick()
{
    SystemState nextState = SystemState::PUMP_LOW_PRESSURE_ERROR;

    
    if (_pressureSensor.getMeasuredPressure() > CONFIG().getLowPressureError())
    {
        _statusHandler.showMessage("Pressure Recovery");
        if (get_state_time_ms() > CONFIG().getLowPressureDelay_ms())
        {
            
            nextState= SystemState::PUMP_OFF;
        }
    }
    else
    {
        _statusHandler.showMessage("Low Pressure Error");
    }
    //else nothing needs to change
    
    return nextState;
};

void StatePumpLowError::enterState() 
{
    _statusHandler.showMessage("Low Pressure Error");
};


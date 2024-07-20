#include <StatePumpLowError.h>
#include <PumpControlConfig.h>

SystemState StatePumpLowError::tick()
{
    SystemState nextState = SystemState::PUMP_LOW_PRESSURE_ERROR;
    
    if (_pressureSensor.getMeasuredPressure() > CONFIG().getLowPressureError())
    {
        _statusHandler.showMessage(MessageId::PRESSURE_RECOVERY);
        nextState= SystemState::PUMP_OFF;    
    }
    else
    {
        _statusHandler.showMessage(MessageId::LOW_PRESSURE_ERROR);
    }
    //else nothing needs to change
    
    return nextState;
};

void StatePumpLowError::enterState() 
{
    _pumpControl.Off();
    _statusHandler.showMessage(MessageId::LOW_PRESSURE_ERROR);
};


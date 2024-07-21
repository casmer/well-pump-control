#include <StatePumpLowError.h>
#include <PumpControlConfig.h>

#define DEBUG_PRINT
SystemState StatePumpLowError::tick()
{
    SystemState nextState = SystemState::PUMP_LOW_PRESSURE_ERROR;
    int measuredPressure = _pressureSensor.getMeasuredPressure();
    if (measuredPressure > CONFIG().getLowPressureError())
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
    #ifdef DEBUG_PRINT
        //Serial.print(5,10);
    #endif
    _pumpControl.Off();
    _statusHandler.showMessage(MessageId::LOW_PRESSURE_ERROR);
};


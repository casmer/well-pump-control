#include <StatePumpLowPressureWait.h>
#include <PumpControlConfig.h>

SystemState StatePumpLowPressureWait::tick()
{
    SystemState nextState = SystemState::PUMP_LOW_PRESSURE_WAIT;
    int measuredPressure = _pressureSensor.getMeasuredPressure();
    if (measuredPressure >= CONFIG().getSetPressureHigh())
    {
        nextState= SystemState::PUMP_OFF;
    }
    else if (measuredPressure <= CONFIG().getSetPressureLow())
    {
        if (get_state_time_ms() >= CONFIG().getLowPressureDelay_ms())
        {
            nextState = SystemState::PUMP_ON;
        } 
        else
        {
            nextState = SystemState::PUMP_LOW_PRESSURE_WAIT;
        }
    }
    else
    {
        nextState = SystemState::PUMP_OFF;
    }

    //TODO: add temperature checks to shut off on overheating conditions
    //else nothing needs to change
    
    
    return nextState;
};

void StatePumpLowPressureWait::enterState() 
{
    _statusHandler.showMessage(MessageId::LOW_PRESSURE_WAIT);
    _pumpControl.Off();
};

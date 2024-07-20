#include <StatePumpOn.h>
#include <PumpControlConfig.h>

SystemState StatePumpOn::tick()
{
    SystemState nextState = SystemState::PUMP_ON;
    int measuredPressure = _pressureSensor.getMeasuredPressure();
    if (measuredPressure >= CONFIG().getSetPressureHigh())
    {
        nextState= SystemState::PUMP_OFF;
    }
    else if ((measuredPressure <= CONFIG().getLowPressureError())
         && (get_state_time_ms() >= CONFIG().getMaxLowPressureRunTime_ms()))
    {
        nextState = SystemState::PUMP_LOW_PRESSURE_ERROR;
    }
    //TODO: add temperature checks to shut off on overheating conditions
    //else nothing needs to change
    
    return nextState;
};

void StatePumpOn::enterState() 
{
    _statusHandler.showMessage(MessageId::PUMP_ON);
    _pumpControl.On();
};

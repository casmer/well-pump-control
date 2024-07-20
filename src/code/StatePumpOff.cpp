#include <StatePumpOff.h>
#include <PumpControlConfig.h>

SystemState StatePumpOff::tick()
{
    SystemState nextState = SystemState::PUMP_OFF;
    int measuredPressure = _pressureSensor.getMeasuredPressure();

    if (measuredPressure <= CONFIG().getSetPressureLow())
    {
        nextState= SystemState::PUMP_LOW_PRESSURE_WAIT;
    }
    //else nothing needs to change
    
    return nextState;
};

void StatePumpOff::enterState() 
{
    _pumpControl.Off();
    _statusHandler.showMessage(MessageId::PUMP_OFF);
};

#include <StatePumpOff.h>
#include <PumpControlConfig.h>

SystemState StatePumpOff::tick()
{
    SystemState nextState = SystemState::PUMP_OFF;
    if (_pressureSensor.getMeasuredPressure() <= CONFIG().getSetPressureLow())
    {
        nextState= SystemState::PUMP_LOW_PRESSURE_WAIT;
    }
    //else nothing needs to change
    
    return nextState;
};

void StatePumpOff::enterState() 
{
    _relayControl.RelayOff();
    _statusHandler.showMessage(MessageId::PUMP_OFF);
};

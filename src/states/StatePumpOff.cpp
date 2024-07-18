#include "states/StatePumpOff.h"
#include "PumpControlConfig.h"

SystemState StatePumpOff::tick()
{
    SystemState nextState = SystemState::PUMP_OFF;
    _relayControl.RelayOff();
    if (_pressureSensor.getMeasuredPressure() <= CONFIG().getSetPressureLow())
    {
        if (_lowPressureWait < CONFIG().getLowPressureDelay_ms())
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

void StatePumpOff::enterState() 
{
    _relayControl.RelayOff();
    _statusHandler.showMessage("Pump Off");
    _lowPressureWait=0;
};

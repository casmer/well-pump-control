#include <StatePumpLowPressureWait.h>
#include <PumpControlConfig.h>

SystemState StatePumpLowPressureWait::tick()
{
    SystemState nextState = SystemState::PUMP_LOW_PRESSURE_WAIT;

    if (_pressureSensor.getMeasuredPressure() >= CONFIG().getSetPressureHigh())
    {
        nextState= SystemState::PUMP_OFF;
    }
    else if ((_pressureSensor.getMeasuredPressure() <= CONFIG().getSetPressureLow())
            && (get_state_time_ms() >= CONFIG().getLowPressureDelay_ms())
        )
    {
        nextState = SystemState::PUMP_LOW_PRESSURE_ERROR;
    }
    else
    {
        nextState = SystemState::PUMP_ON;
    }

    //TODO: add temperature checks to shut off on overheating conditions
    //else nothing needs to change
    
    
    return nextState;
};

void StatePumpLowPressureWait::enterState() 
{
    _pumpControl.Off();
};

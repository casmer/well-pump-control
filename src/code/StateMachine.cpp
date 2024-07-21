



#include <StateMachine.h>
#define PRINT_STATE

StateMachine::StateMachine(StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl) :
    _statePumpOff(statusHandler, pressureSensor, relayControl), 
    _statePumpLowPressureWait(statusHandler, pressureSensor, relayControl), 
    _statePumpOn(statusHandler, pressureSensor, relayControl), 
    _statePumpLowError(statusHandler, pressureSensor, relayControl),
    _states{
        &_statePumpOff, 
        &_statePumpLowPressureWait, 
        &_statePumpOn, 
        &_statePumpLowError
    },
    _statusHandler(statusHandler),
    _pressureSensor(pressureSensor),
    _pumpControl(relayControl),
    _currentState{SystemState::PUMP_OFF}
 
{};

void StateMachine::setup()
{
    _states[static_cast<int>(_currentState)]->tick();
}

SystemState StateMachine::tick()
{
    
    SystemState nextState = getCurrentState().tick();
        #ifdef PRINT_STATE
            Serial.print("State Change: ");
            Serial.print(static_cast<int>(_currentState));
            Serial.print(" -> ");
            Serial.print(static_cast<int>(nextState));
            Serial.println("...");
        #endif
    if (nextState!=_currentState)
    {
        _states[static_cast<int>(nextState)]->enter();
        _currentState=nextState;
    }
    if (_currentState==SystemState::PUMP_ON || _currentState==SystemState::PUMP_LOW_PRESSURE_WAIT)
    {
        _statusHandler.updateTime(getCurrentState().get_state_time_ms());
    }
    else 
    {
        _statusHandler.updateTime(0);
    }
    _statusHandler.updatePumpState(_pumpControl.isOn());
    
    return _currentState;
}








#include "states/StateMachine.h"

StateMachine::StateMachine(StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl) :
          states{
    StatePumpOff(statusHandler, pressureSensor, relayControl), 
    StatePumpOn(statusHandler, pressureSensor, relayControl), 
    StatePumpLowError(statusHandler, pressureSensor, relayControl)
  },
  _statusHandler(statusHandler),
  _pressureSensor(pressureSensor),
  _relayControl(relayControl),
 _currentState{SystemState::PUMP_OFF}
 
{};

SystemState StateMachine::tick()
{
    
    switch (_currentState)
    {
    case SystemState::PUMP_OFF:
        /* code */
        break;
    case SystemState::PUMP_LOW_PRESSURE_WAIT:
        /* code */
        break;
    case SystemState::PUMP_ON:
        /* code */
        break;
    case SystemState::PUMP_LOW_PRESSURE_ERROR:
        /* code */
        break;
    }

    return _currentState;
}




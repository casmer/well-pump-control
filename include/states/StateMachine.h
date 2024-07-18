

#ifndef STATES_STATE_MACHINE_H
#define STATES_STATE_MACHINE_H


#include "RelayControl.h"
#include "StatusHandler.h"
#include "PressureSensor.h"
#include "states/State.h"
#include "states/StatePumpOff.h"
#include "states/StatePumpOn.h"
#include "states/StatePumpLowError.h"


class StateMachine
{
public:
  StateMachine(StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl);
  SystemState tick();
private:
  //state variables
  State states[3];
  // interface handlers
  StatusHandler& _statusHandler;
  PressureSensor& _pressureSensor;
  RelayControl& _relayControl;
  SystemState _currentState;
};



#endif //STATES_STATE_MACHINE_H
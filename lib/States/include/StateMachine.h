#ifndef STATES_STATE_MACHINE_H
#define STATES_STATE_MACHINE_H


#include <RelayControl.h>
#include <StatusHandler.h>
#include <PressureSensor.h>
#include <State.h>
#include <StatePumpOff.h>
#include <StatePumpOn.h>
#include <StatePumpLowError.h>
#include <StatePumpLowPressureWait.h>

class StateMachine
{
public:
  StateMachine(StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl);
  /// @brief should be run on every loop of the mcu.
  /// @return returns the current state of the state machine.
  SystemState tick();
  /// @brief setup the state machine. (should be called from mcu setup)
  void setup();
private:
  //state variables
  State _states[4];
  // interface handlers
  StatusHandler& _statusHandler;
  PressureSensor& _pressureSensor;
  RelayControl& _relayControl;
  SystemState _currentState;
};

#endif //STATES_STATE_MACHINE_H
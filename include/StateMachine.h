// Copyright (C) 2024 Casey Gregoire <caseyg@lalosoft.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.

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

  StatePumpOff _statePumpOff;
  StatePumpLowPressureWait  _statePumpLowPressureWait;
  StatePumpOn _statePumpOn;
  StatePumpLowError _statePumpLowError;

  //state variables
  State* _states[4];
  // interface handlers
  StatusHandler& _statusHandler;
  PressureSensor& _pressureSensor;
  RelayControl& _pumpControl;
  SystemState _currentState;
  State& getCurrentState() { return *_states[static_cast<int>(_currentState)]; };

};

#endif //STATES_STATE_MACHINE_H
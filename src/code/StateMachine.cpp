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




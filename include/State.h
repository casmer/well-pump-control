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

#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include <PressureSensor.h>
#include <RelayControl.h>
#include <StatusHandler.h>

enum class SystemState : int
{
    PUMP_OFF = 0,
    PUMP_LOW_PRESSURE_WAIT = 1,
    PUMP_ON = 2,
    PUMP_LOW_PRESSURE_ERROR = 3
};

class State
{
    public:
        State( StatusHandler& statusHandler, PressureSensor& pressureSensor, RelayControl& relayControl):
        _statusHandler(statusHandler),
        _pressureSensor(pressureSensor),
        _pumpControl(relayControl),
        _state_entry_time(0)
         {};
        virtual SystemState tick() =0;
        void enter();
        unsigned long get_state_time_ms();
        unsigned long get_last_state_time_ms();

    protected:
        virtual void enterState() {};
        StatusHandler&  _statusHandler;
        PressureSensor& _pressureSensor;
        RelayControl&  _pumpControl;
    private:
        unsigned long _state_entry_time;
        unsigned long _last_state_time;
};

#endif //SYSTEM_STATE_H
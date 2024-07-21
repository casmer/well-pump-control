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

#include <StatePumpLowPressureWait.h>
#include <PumpControlConfig.h>

SystemState StatePumpLowPressureWait::tick()
{
    SystemState nextState = SystemState::PUMP_LOW_PRESSURE_WAIT;
    int measuredPressure = _pressureSensor.getMeasuredPressure();
    if (measuredPressure >= CONFIG().getSetPressureHigh())
    {
        nextState= SystemState::PUMP_OFF;
    }
    else if (measuredPressure <= CONFIG().getSetPressureLow())
    {
        if (get_state_time_ms() >= CONFIG().getLowPressureDelay_ms())
        {
            nextState = SystemState::PUMP_ON;
        } 
        else
        {
            nextState = SystemState::PUMP_LOW_PRESSURE_WAIT;
        }
    }
    else
    {
        nextState = SystemState::PUMP_OFF;
    }

    //TODO: add temperature checks to shut off on overheating conditions
    //else nothing needs to change
    
    
    return nextState;
};

void StatePumpLowPressureWait::enterState() 
{
    _statusHandler.showMessage(MessageId::LOW_PRESSURE_WAIT);
    _pumpControl.Off();
};

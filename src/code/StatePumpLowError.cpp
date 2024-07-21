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

#include <StatePumpLowError.h>
#include <PumpControlConfig.h>

#define DEBUG_PRINT
SystemState StatePumpLowError::tick()
{
    SystemState nextState = SystemState::PUMP_LOW_PRESSURE_ERROR;
    int measuredPressure = _pressureSensor.getMeasuredPressure();
    if (measuredPressure > CONFIG().getLowPressureError())
    {
        _statusHandler.showMessage(MessageId::PRESSURE_RECOVERY);
        nextState= SystemState::PUMP_OFF;    
    }
    else
    {
        _statusHandler.showMessage(MessageId::LOW_PRESSURE_ERROR);
    }
    //else nothing needs to change
    
    return nextState;
};

void StatePumpLowError::enterState() 
{
    #ifdef DEBUG_PRINT
        //Serial.print(5,10);
    #endif
    _pumpControl.Off();
    _statusHandler.showMessage(MessageId::LOW_PRESSURE_ERROR);
};


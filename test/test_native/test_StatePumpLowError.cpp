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

#include <ArduinoFake.h>
#include <StatePumpLowError.h>
#include <PumpControlConfig.h>
#include <mocks/TestHelpers.h>
#include <unity.h>

#include <cstdio>

using namespace fakeit;

void test_StatePumpLowError_pressure_recovery(void)
{
    When(Method(ArduinoFake(), millis)).Return(2003);
    Mock<PressureSensor> pressureSensor;
    When(Method(pressureSensor, setup)).AlwaysReturn();
    When(Method(pressureSensor, readPressure)).AlwaysReturn();
    When(Method(pressureSensor, getMeasuredPressure)).Return(60, 30, 10, 20);
    Mock<RelayControl> relayControl;
    When(Method(relayControl, On)).AlwaysReturn();
    When(Method(relayControl, Off)).AlwaysReturn();
    When(Method(relayControl, setDioPin)).AlwaysReturn();
    When(Method(relayControl, isOn)).Return(false);

    Mock<StatusHandler> statusHandler;

    When(Method(statusHandler, setup)).AlwaysReturn();
    When(Method(statusHandler, updatePressure)).AlwaysReturn();
    When(Method(statusHandler, showMessage)).AlwaysReturn();

    StatePumpLowError uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
     
    uut.enter();
    SystemState nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1_Times);
    
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(1_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(1_Times);
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_OFF, nextState);

}


void test_StatePumpLowError_no_recovery(void)
{
    When(Method(ArduinoFake(), millis)).Return(2003,MINUTES_ms(20));
    Mock<PressureSensor> pressureSensor;
    When(Method(pressureSensor, setup)).AlwaysReturn();
    When(Method(pressureSensor, readPressure)).AlwaysReturn();
    When(Method(pressureSensor, getMeasuredPressure)).Return(5, 5);
    Mock<RelayControl> relayControl;
    When(Method(relayControl, On)).AlwaysReturn();
    When(Method(relayControl, Off)).AlwaysReturn();
    When(Method(relayControl, setDioPin)).AlwaysReturn();
    When(Method(relayControl, isOn)).Return(false);

    Mock<StatusHandler> statusHandler;

    When(Method(statusHandler, setup)).AlwaysReturn();
    When(Method(statusHandler, updatePressure)).AlwaysReturn();
    When(Method(statusHandler, showMessage)).AlwaysReturn();

    StatePumpLowError uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
     
    uut.enter();
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(1_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    SystemState nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1);
    
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(2_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_LOW_PRESSURE_ERROR, nextState);
    nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1);
    
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(3_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_LOW_PRESSURE_ERROR, nextState);
}

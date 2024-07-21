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
#include <StatePumpLowPressureWait.h>
#include <PumpControlConfig.h>
#include <mocks/TestHelpers.h>
#include <unity.h>

using namespace fakeit;

void test_StatePumpLowPressureWait_pressure_high(void)
{

    When(Method(ArduinoFake(), millis)).Return(2003, 4000);
    Mock<PressureSensor> pressureSensor;
    When(Method(pressureSensor, setup)).AlwaysReturn();
    When(Method(pressureSensor, readPressure)).AlwaysReturn();
    When(Method(pressureSensor, getMeasuredPressure)).AlwaysReturn(CONFIG().getSetPressureHigh());
    Mock<RelayControl> relayControl;
    When(Method(relayControl, On)).AlwaysReturn();
    When(Method(relayControl, Off)).AlwaysReturn();
    When(Method(relayControl, setDioPin)).AlwaysReturn();
    When(Method(relayControl, isOn)).Return(false);

    Mock<StatusHandler> statusHandler;

    When(Method(statusHandler, setup)).AlwaysReturn();
    When(Method(statusHandler, updatePressure)).AlwaysReturn();
    When(Method(statusHandler, showMessage)).AlwaysReturn();

    StatePumpLowPressureWait uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
     
    uut.enter();
    SystemState nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1_Times);
    
    Verify(Method(statusHandler, showMessage).Using(MessageId::PUMP_OFF)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_WAIT)).Exactly(1_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PUMP_ON)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(0_Times);
  
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_OFF, nextState);
}

void test_StatePumpLowPressureWait_pressure_low(void)
{

    When(Method(ArduinoFake(), millis)).Return(
            0, // just started
            CONFIG().getLowPressureDelay_ms()-1, //for pressure low error, but not long enough
            CONFIG().getLowPressureDelay_ms(), //for pressure low error, long enough to stop
            MINUTES_ms(5),MINUTES_ms(5),MINUTES_ms(5),MINUTES_ms(5));
    Mock<PressureSensor> pressureSensor;
    When(Method(pressureSensor, setup)).AlwaysReturn();
    When(Method(pressureSensor, readPressure)).AlwaysReturn();
    When(Method(pressureSensor, getMeasuredPressure)).Return(CONFIG().getSetPressureLow()+1,
         CONFIG().getSetPressureLow(), CONFIG().getSetPressureLow(), CONFIG().getSetPressureHigh());
    Mock<RelayControl> relayControl;
    When(Method(relayControl, On)).AlwaysReturn();
    When(Method(relayControl, Off)).AlwaysReturn();
    When(Method(relayControl, setDioPin)).AlwaysReturn();
    When(Method(relayControl, isOn)).Return(false);

    Mock<StatusHandler> statusHandler;

    When(Method(statusHandler, setup)).AlwaysReturn();
    When(Method(statusHandler, updatePressure)).AlwaysReturn();
    When(Method(statusHandler, showMessage)).AlwaysReturn();
    
    StatePumpLowPressureWait uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
    int expect_millis_call_count=1;
    uut.enter();
    Verify(Method(ArduinoFake(), millis)).Exactly(expect_millis_call_count);

    // tick 1, pressure low, but not low enough
    SystemState nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(expect_millis_call_count);
    TEST_ASSERT_EQ_ENH(0, uut.get_last_state_time_ms());
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_OFF, nextState);
    
    // tick 2, pressure low enough, but not long enough
    nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(++expect_millis_call_count);
    
    TEST_ASSERT_EQ_ENH(CONFIG().getLowPressureDelay_ms()-1, uut.get_last_state_time_ms());
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_LOW_PRESSURE_WAIT, nextState);

    // tick 2, pressure low enough, and long enough
    nextState= uut.tick();
    TEST_ASSERT_EQ_ENH(CONFIG().getLowPressureDelay_ms(), uut.get_last_state_time_ms());
    Verify(Method(ArduinoFake(), millis)).Exactly(++expect_millis_call_count);
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_ON, nextState);

    // tick 3, pressure high enough to be off
    nextState= uut.tick();
    TEST_ASSERT_EQ_ENH(CONFIG().getLowPressureDelay_ms(), uut.get_last_state_time_ms());
    Verify(Method(ArduinoFake(), millis)).Exactly(expect_millis_call_count);
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_OFF, nextState);

    Verify(Method(statusHandler, showMessage).Using(MessageId::PUMP_OFF)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_WAIT)).Exactly(1_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PUMP_ON)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(0_Times);
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_OFF, nextState);
}



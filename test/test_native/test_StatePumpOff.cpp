#include <ArduinoFake.h>
#include <StatePumpOff.h>
#include <PumpControlConfig.h>
#include <mocks/TestHelpers.h>
#include <unity.h>


using namespace fakeit;

void StatePumpOff_pressure_low(void)
{

    When(Method(ArduinoFake(), millis)).Return(2003, 4000);
    Mock<PressureSensor> pressureSensor;
    When(Method(pressureSensor, setup)).AlwaysReturn();
    When(Method(pressureSensor, readPressure)).AlwaysReturn();
    When(Method(pressureSensor, getMeasuredPressure)).AlwaysReturn(CONFIG().getSetPressureLow());
    Mock<RelayControl> relayControl;
    When(Method(relayControl, On)).AlwaysReturn();
    When(Method(relayControl, Off)).AlwaysReturn();
    When(Method(relayControl, setDioPin)).AlwaysReturn();
    When(Method(relayControl, isOn)).Return(false);

    Mock<StatusHandler> statusHandler;

    When(Method(statusHandler, setup)).AlwaysReturn();
    When(Method(statusHandler, updatePressure)).AlwaysReturn();
    When(Method(statusHandler, showMessage)).AlwaysReturn();
    When(Method(statusHandler, printTime)).AlwaysReturn();

    StatePumpOff uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
     
    uut.enter();
    SystemState nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1_Times);
    
    Verify(Method(statusHandler, showMessage).Using(MessageId::PUMP_OFF)).Exactly(1_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_WAIT)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PUMP_ON)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(0_Times);
  
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_LOW_PRESSURE_WAIT, nextState);

}


void StatePumpOff_pressure_high(void)
{

    When(Method(ArduinoFake(), millis)).Return(2003,MINUTES_ms(20));
    Mock<PressureSensor> pressureSensor;
    When(Method(pressureSensor, setup)).AlwaysReturn();
    When(Method(pressureSensor, readPressure)).AlwaysReturn();
    When(Method(pressureSensor, getMeasuredPressure)).Return(CONFIG().getSetPressureLow()+1, CONFIG().getSetPressureHigh()+1);
    Mock<RelayControl> relayControl;
    When(Method(relayControl, On)).AlwaysReturn();
    When(Method(relayControl, Off)).AlwaysReturn();
    When(Method(relayControl, setDioPin)).AlwaysReturn();
    When(Method(relayControl, isOn)).Return(false);

    Mock<StatusHandler> statusHandler;

    When(Method(statusHandler, setup)).AlwaysReturn();
    When(Method(statusHandler, updatePressure)).AlwaysReturn();
    When(Method(statusHandler, showMessage)).AlwaysReturn();
    When(Method(statusHandler, printTime)).AlwaysReturn();


    StatePumpOff uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
    
    uut.enter();
    SystemState nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1_Times);
    

    TEST_ASSERT_EQ_ENH(SystemState::PUMP_OFF, nextState);
    nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1_Times);
    
    Verify(Method(statusHandler, showMessage).Using(MessageId::PUMP_OFF)).Exactly(1_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_WAIT)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PUMP_ON)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(0_Times);
    TEST_ASSERT_EQ_ENH(SystemState::PUMP_OFF, nextState);
}


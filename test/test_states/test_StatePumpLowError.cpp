#include <ArduinoFake.h>
#include <StatePumpLowError.h>
#include <mocks/TestHelpers.h>
#include <unity.h>


using namespace fakeit;

void setUp(void)
{
     ArduinoFakeReset();
}

void tearDown(void) {
    // clean stuff up here
}

void test_pressure_recovery(void)
{

    When(Method(ArduinoFake(), millis)).Return(2003);
    Mock<PressureSensor> pressureSensor;
    When(Method(pressureSensor, setup)).AlwaysReturn();
    When(Method(pressureSensor, readPressure)).AlwaysReturn();
    When(Method(pressureSensor, getMeasuredPressure)).Return(60, 30, 10, 20);
    Mock<RelayControl> relayControl;
    When(Method(relayControl, RelayOn)).AlwaysReturn();
    When(Method(relayControl, RelayOff)).AlwaysReturn();
    When(Method(relayControl, setRelayPin)).AlwaysReturn();
    When(Method(relayControl, getRelayIsOn)).Return(false);

    Mock<StatusHandler> statusHandler;

    When(Method(statusHandler, setup)).AlwaysReturn();
    When(Method(statusHandler, updatePressure)).AlwaysReturn();
    When(Method(statusHandler, showMessage)).AlwaysReturn();
    When(Method(statusHandler, printTime)).AlwaysReturn();


    StatePumpLowError uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
     
    uut.enter();
    SystemState nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1_Times);
    
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(1_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(1_Times);
    TEST_ASSERT_EQUAL(SystemState::PUMP_OFF, nextState);

    /*
    MyService service(clientMock);

    String response = service.request("myserver.com");
    TEST_ASSERT_EQUAL(3, response.length());
    TEST_ASSERT_TRUE(response.equals("200"));


    */
}


void test_pressure_no_recovery(void)
{

    When(Method(ArduinoFake(), millis)).Return(2003,MINUTES_ms(20));
    Mock<PressureSensor> pressureSensor;
    When(Method(pressureSensor, setup)).AlwaysReturn();
    When(Method(pressureSensor, readPressure)).AlwaysReturn();
    When(Method(pressureSensor, getMeasuredPressure)).Return(5, 5);
    Mock<RelayControl> relayControl;
    When(Method(relayControl, RelayOn)).AlwaysReturn();
    When(Method(relayControl, RelayOff)).AlwaysReturn();
    When(Method(relayControl, setRelayPin)).AlwaysReturn();
    When(Method(relayControl, getRelayIsOn)).Return(false);

    Mock<StatusHandler> statusHandler;

    When(Method(statusHandler, setup)).AlwaysReturn();
    When(Method(statusHandler, updatePressure)).AlwaysReturn();
    When(Method(statusHandler, showMessage)).AlwaysReturn();
    When(Method(statusHandler, printTime)).AlwaysReturn();


     StatePumpLowError uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
     
     uut.enter();
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(1_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    SystemState nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1);
    
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(2_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    TEST_ASSERT_EQUAL(SystemState::PUMP_LOW_PRESSURE_ERROR, nextState);
    nextState= uut.tick();
    Verify(Method(ArduinoFake(), millis)).Exactly(1);
    
    Verify(Method(statusHandler, showMessage).Using(MessageId::LOW_PRESSURE_ERROR)).Exactly(3_Times);
    Verify(Method(statusHandler, showMessage).Using(MessageId::PRESSURE_RECOVERY)).Exactly(0_Times);
    TEST_ASSERT_EQUAL(SystemState::PUMP_LOW_PRESSURE_ERROR, nextState);
}

void RUN_UNITY_TESTS() {
    UNITY_BEGIN();
    RUN_TEST(test_pressure_recovery);
    RUN_TEST(test_pressure_no_recovery);
    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>
void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    RUN_UNITY_TESTS();
}

void loop() {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}

#else

int main(int argc, char **argv) {
    RUN_UNITY_TESTS();
    return 0;
}

#endif
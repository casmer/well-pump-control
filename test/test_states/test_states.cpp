#include <gtest/gtest.h>


#include <StatePumpLowError.h>
//using namespace fakeit;

void setUp(void)
{
    // ArduinoFakeReset();
}

void tearDown(void) {
    // clean stuff up here
}

void test_connect(void)
{
    // Mock<PressureSensor> pressureSensor;
    // When(Method(pressureSensor, setup)).AlwaysReturn();
    // When(Method(pressureSensor, readPressure)).AlwaysReturn();
    // When(Method(pressureSensor, getMeasuredPressure)).Return(20, 30, 10, 20);
    
    // Mock<RelayControl> relayControl;
    // When(Method(relayControl, RelayOn)).AlwaysReturn();
    // When(Method(relayControl, RelayOff)).AlwaysReturn();
    // When(Method(relayControl, setRelayPin)).AlwaysReturn();
    // When(Method(relayControl, getRelayIsOn)).Return(false);

    // Mock<StatusHandler> statusHandler;
    
    

    // StatePumpLowError uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
    
  //  uut.enter();
    EXPECT_TRUE(true);
    /*
    MyService service(clientMock);

    String response = service.request("myserver.com");
    TEST_ASSERT_EQUAL(3, response.length());
    TEST_ASSERT_TRUE(response.equals("200"));

    Verify(Method(ArduinoFake(Client), stop)).Once();
    Verify(Method(ArduinoFake(Client), available)).Exactly(4_Times);
    Verify(OverloadedMethod(ArduinoFake(Client), read, int())).Exactly(3_Times);

    Verify(OverloadedMethod(ArduinoFake(Client), println, size_t())).Once();
    Verify(OverloadedMethod(ArduinoFake(Client), println, size_t(const char [])).Using((const char *)"STATUS")).Never();
    Verify(OverloadedMethod(ArduinoFake(Client), connect, int(const char[], uint16_t)).Using((const char *)"myserver.com", 80)).Once();
    */
}

#if defined(ARDUINO)
#include <Arduino.h>

void setup()
{
    // should be the same value as for the `test_speed` option in "platformio.ini"
    // default value is test_speed=115200
    Serial.begin(115200);

    ::testing::InitGoogleTest();
}

void loop()
{
	// Run tests
	if (RUN_ALL_TESTS())
	;

	// sleep 1 sec
	delay(1000);
}

#else
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
	if (RUN_ALL_TESTS())
	;
	// Always return zero-code and allow PlatformIO to parse results
	return 0;
}
#endif
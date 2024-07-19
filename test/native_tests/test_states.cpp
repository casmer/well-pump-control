#include <Arduino.h>
#include <PressureSensor.h>
#include <RelayControl.h>
#include "StatusHandler.h"



#include "StatePumpLowError.h"
#include <unity.h>
using namespace fakeit;

void setUp(void)
{
    ArduinoFakeReset();
}

void tearDown(void) {
    // clean stuff up here
}

void test_connect(void)
{
    Mock<PressureSensor> pressureSensor;
    When(Method(pressureSensor, setup)).AlwaysReturn();
    When(Method(pressureSensor, readPressure)).AlwaysReturn();
    When(Method(pressureSensor, getMeasuredPressure)).Return(20, 30, 10, 20);
    
    Mock<RelayControl> relayControl;
    When(Method(relayControl, RelayOn)).AlwaysReturn();
    When(Method(relayControl, RelayOff)).AlwaysReturn();
    When(Method(relayControl, setRelayPin)).AlwaysReturn();
    When(Method(relayControl, getRelayIsOn)).Return(false);

    Mock<StatusHandler> statusHandler;
    
    

    StatePumpLowError uut(statusHandler.get(), pressureSensor.get(), relayControl.get());
    
    uut.enter();
    
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

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_connect);

    return UNITY_END();
}
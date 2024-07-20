#include <ArduinoFake.h>
#include <unity.h>

void test_pressure_recovery(void);
void test_pressure_no_recovery(void);
void test_pump_off_pressure_low(void);
void test_pump_off_pressure_high(void);
void test_pump_on_pressure_low(void);
void test_pump_on_pressure_high(void);

void setUp(void)
{
     ArduinoFakeReset();
}

void tearDown(void) {
    // clean stuff up here
}


void RUN_UNITY_TESTS() {
    UNITY_BEGIN();
    RUN_TEST(test_pressure_recovery);
    RUN_TEST(test_pressure_no_recovery);

    RUN_TEST(test_pump_off_pressure_low);
    RUN_TEST(test_pump_off_pressure_high);

    RUN_TEST(test_pump_on_pressure_low);
    RUN_TEST(test_pump_on_pressure_high);

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
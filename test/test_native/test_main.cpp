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
#include <unity.h>

void test_StatePumpLowError_pressure_recovery(void);
void test_StatePumpLowError_no_recovery(void);
void StatePumpOff_pressure_low(void);
void StatePumpOff_pressure_high(void);
void test_StatePumpOn_pressure_low(void);
void test_StatePumpOn_pressure_high(void);
void test_StatePumpLowPressureWait_pressure_low(void);
void test_StatePumpLowPressureWait_pressure_high(void);

void setUp(void)
{
     ArduinoFakeReset();
}

void tearDown(void) {
    // clean stuff up here
}


void RUN_UNITY_TESTS() {
    UNITY_BEGIN();
    RUN_TEST(test_StatePumpLowError_pressure_recovery);
    RUN_TEST(test_StatePumpLowError_no_recovery);

    RUN_TEST(StatePumpOff_pressure_low);
    RUN_TEST(StatePumpOff_pressure_high);

    RUN_TEST(test_StatePumpOn_pressure_low);
    RUN_TEST(test_StatePumpOn_pressure_high);

    RUN_TEST(test_StatePumpLowPressureWait_pressure_low);
    RUN_TEST(test_StatePumpLowPressureWait_pressure_high);
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
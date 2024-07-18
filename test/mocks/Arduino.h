#include <gmock/gmock.h>

class ArduinoMock {
  private:
    unsigned long  currentMillis;

  public:
    ArduinoMock();

    unsigned long getMillis() {
      return currentMillis;
    };

    void setMillis (unsigned long milliseconds) {
      currentMillis = milliseconds;
    };
 
    void addMillis (unsigned long milliseconds) {
      currentMillis += milliseconds;
    };
   

    MOCK_METHOD2(pinMode, void (uint8_t, uint8_t));
    MOCK_METHOD2(analogWrite, void (uint8_t, int));
    MOCK_METHOD2(digitalWrite, void (uint8_t, uint8_t));
    MOCK_METHOD1(digitalRead, int (int));
    MOCK_METHOD1(analogRead, int (int));
    MOCK_METHOD1(delay, void (int));
    MOCK_METHOD0(millis, unsigned long ());
};
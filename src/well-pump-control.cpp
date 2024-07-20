

#include <ArduinoBLE.h>
#include <Arduino.h>
#include <loopTimer.h>
#include "digital_pin_defs.h"
#include <pins_arduino.h>
// install the loopTimer library from https://www.forward.com.au/pfod/ArduinoProgramming/RealTimeArduino/TimingDelaysInArduino.html
// loopTimer.h also needs the millisDelay library installed from https://www.forward.com.au/pfod/ArduinoProgramming/TimingDelaysInArduino.html
#include <BufferedOutput.h>
// install SafeString library from Library manager or from https://www.forward.com.au/pfod/ArduinoProgramming/SafeString/index.html
// to get BufferedOutput. See https://www.forward.com.au/pfod/ArduinoProgramming/Serial_IO/index.html for a full tutorial
// on Arduino Serial I/O that Works
#include <RelayControl.h>
#include <StatusHandler.h>
#include <PressureSensor.h>
#include <StateMachine.h>

/*

*/
//
//int D0=16; //IO
//int D1=5;  //IO, SCL
//int D2=4;  //IO, SCA
//int D3=0;  //IO, 10k Pull-up
//int D4=2;  //IO, 10k Pull-up, BUILTIN_LED
//int D5=14; //IO, SCK
//int D6=12; //IO, MISO
//int D7=13; //IO, MOSI
//int D8=5;  //IO, 10k Pull-down, SS

#include "MAX6675.h"
const int selectPin = D7;
MAX6675 thermoCouple(selectPin, &SPI);
uint32_t thermoCoupleSpeed = 500; 
float tempF = 0.0f;

// constant for seconds in a minute.
#define MINUTE 60
// Configuration
int setPressure = 45;
int minPressure = 30;
int minPressureDebounceCount = 3;
int maxRunTime = 30*MINUTE;
int pumpCooldownTime = 5*MINUTE;
int blinkTime_ms = 1000;
int pressureCheckTime_ms = 500;
int statusUpdateTime_ms = 2000;
createBufferedOutput(bufferedOut, 80, DROP_UNTIL_EMPTY);
// Pin Assignments
int relayPin = D5;
int blinkPin = LED_BUILTIN;
int pressureSensorPin = A0;

//delay objects
millisDelay ledDelay;
millisDelay pressureCheckDelay;
millisDelay statusUpdateDelay;

// interface handlers
RelayControl relayControl;
StatusHandler statusHandler;
PressureSensor pressureSensor;
//state machine
StateMachine stateMachine(statusHandler, pressureSensor, relayControl);

bool ledOn = false;
int pumpOnTime = 0;
int pumpOnUnderPressureTime = 0; 
int minPressureCounter = 0;


//because we use time pump was on for cool down we need to add it to the max run time for comparison.
int  pumpCooldownCheckTime = pumpCooldownTime;

/*
I2C device found at address 0x27  ! LCD
I2C device found at address 0x48  !
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  

  pinMode(relayPin, OUTPUT);
  pinMode(blinkPin, OUTPUT);
  pinMode(pressureSensorPin, INPUT);
  relayControl.setDioPin(relayPin);
  pressureSensor.setup();\
  Serial.begin(74880);
  
  bufferedOut.connect(Serial, 74880);
  statusHandler.setup();
  
  SPI.begin();
  thermoCouple.begin();

  ledDelay.start(blinkTime_ms);
  pressureCheckDelay.start(pressureCheckTime_ms);
  statusUpdateDelay.start(statusUpdateTime_ms);
  
}

void blinkLed()
{
  if (ledDelay.justFinished()) 
  {
    ledDelay.repeat(); 

    ledOn = !ledOn;    
    digitalWrite(blinkPin, ledOn ? HIGH : LOW); 
  } 
}

void statusUpdate()
{
  if (statusUpdateDelay.justFinished())
  {
    uint32_t start, stop;

    ////////// THERMOCOUPLE //////////////////
    //thermoCouple.setSPIspeed(thermoCoupleSpeed);

    start = micros();
    int status = thermoCouple.read();
    stop = micros();
    float temp = thermoCouple.getTemperature();

    tempF = (temp * 1.8) + 32.0;
    Serial.print(millis());
    // Serial.print("\tspeed: ");
    // Serial.print(thermoCoupleSpeed / 1000);
    Serial.print("\tstatus: ");
    Serial.print(status);
    Serial.print("\ttemp: ");
    Serial.print(temp);
    Serial.print("\tus: ");
    Serial.println(stop - start);
      ////////// THERMOCOUPLE //////////////////
    Serial.print("temp:");
    Serial.println(tempF, 2);

    statusUpdateDelay.repeat();
    
  }
}


void processPressure()
{
  if (pressureCheckDelay.justFinished()) 
  {
    pressureCheckDelay.repeat(); 

    
  } 
  
  
  
  
}
// the loop function runs over and over again forever
void loop() {
  //
  
  processPressure();
  delay(100);                       // wait for a second
  blinkLed();
  statusUpdate();  
  
}

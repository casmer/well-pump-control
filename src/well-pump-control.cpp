

#include <ArduinoBLE.h>
#include <Arduino.h>
#include <loopTimer.h>
#include "digital_pin_defs.h"
#include <pins_arduino.h>
#include <RelayControl.h>
#include <StatusHandler.h>
#include <PressureSensor.h>
#include <StateMachine.h>

#include "MAX6675.h"
const int selectPin = D7;
MAX6675 thermoCouple(selectPin, &SPI);
uint32_t thermoCoupleSpeed = 500; 

// Configuration
int blinkTime_ms = 1000;
int pressureCheckTime_ms = 200;
int statusUpdateTime_ms = 200;
// Pin Assignments
int relayPin = D6;
int blinkPin = D8;
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

/*
I2C device found at address 0x27  ! LCD
I2C device found at address 0x48  !
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  

  pinMode(relayPin, OUTPUT);
  pinMode(blinkPin, OUTPUT);
  digitalWrite(blinkPin, LOW);
  pinMode(pressureSensorPin, INPUT);
  relayControl.setDioPin(relayPin);
  pressureSensor.setup();
  Serial.begin(74880);
  
  statusHandler.setup();
  
  SPI.begin();
  thermoCouple.begin();

  stateMachine.setup();

  ledDelay.start(blinkTime_ms);
  pressureCheckDelay.start(pressureCheckTime_ms);
  statusUpdateDelay.start(statusUpdateTime_ms);
  
}

void blinkLed()
{
  if (ledDelay.justFinished()) 
  {
    ledOn = !ledOn;    
    digitalWrite(blinkPin, ledOn ? HIGH : LOW); 
    ledDelay.repeat(); 
  } 
}

void statusUpdate()
{
  if (statusUpdateDelay.justFinished())
  {
    statusHandler.printAll();
    statusUpdateDelay.repeat();    
  }
}

void processPressure()
{
  if (pressureCheckDelay.justFinished()) 
  {
    pressureSensor.readPressure();
    statusHandler.updatePressure(pressureSensor.getMeasuredPressure());
    pressureCheckDelay.repeat(); 
  } 
}
// the loop function runs over and over again forever
void loop() {
  //
  stateMachine.tick();
  
  processPressure();
  blinkLed();
  statusUpdate();  
  
  delay(250);     //loop time.
}

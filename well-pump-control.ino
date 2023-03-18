

#include <ESP8266WiFi.h>

#include <loopTimer.h>
// install the loopTimer library from https://www.forward.com.au/pfod/ArduinoProgramming/RealTimeArduino/TimingDelaysInArduino.html
// loopTimer.h also needs the millisDelay library installed from https://www.forward.com.au/pfod/ArduinoProgramming/TimingDelaysInArduino.html
#include <BufferedOutput.h>
// install SafeString library from Library manager or from https://www.forward.com.au/pfod/ArduinoProgramming/SafeString/index.html
// to get BufferedOutput. See https://www.forward.com.au/pfod/ArduinoProgramming/Serial_IO/index.html for a full tutorial
// on Arduino Serial I/O that Works
#include "RelayControl.h"
#include "StatusHandler.h"
#include "PressureSensor.h"
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
int statusUpdateTime_ms = 500;
createBufferedOutput(bufferedOut, 80, DROP_UNTIL_EMPTY);

// Pin Assignments
int relayPin = D5;
int blinkPin = BUILTIN_LED;
int pressureSensorPin = A0;

//delay objects
millisDelay ledDelay;
millisDelay pressureCheckDelay;
millisDelay statusUpdateDelay;
RelayControl relayControl;
StatusHandler statusHandler;
PressureSensor pressureSensor;
//state variables

bool ledOn = false;
int pumpOnTime = 0;
int pumpOnUnderPressureTime = 0;
int minPressureCounter = 0;

//because we use time pump was on for cool down we need to add it to the max run time for comparison.
int  pumpCooldownCheckTime = pumpCooldownTime;



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(relayPin, OUTPUT);
  pinMode(blinkPin, OUTPUT);
  pinMode(pressureSensorPin, INPUT);
  relayControl.setRelayPin(relayPin);
  pressureSensor.setup(pressureSensorPin);
  Serial.begin(74880);
  bufferedOut.connect(Serial);
  statusHandler.setup();
  
  ledDelay.start(blinkTime_ms);
  pressureCheckDelay.start(pressureCheckTime_ms);
  statusUpdateDelay.start(statusUpdateTime_ms)
  
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
    statusUpdateDelay.repeat();
    //TODO: Status update.
  }
}


void processPressure()
{
  pressureSensor.readPressure();
  if (pressureSensor.getMeasuredPressure() >= setPressure)
  {
    relayControl.RelayOff();
    pumpOnTime=0;
    pumpOnUnderPressureTime=0;
    minPressureCounter=0;
  } else if (pumpOnUnderPressureTime >= maxRunTime)
  {
    relayControl.RelayOff();
  } else
  if (pressureSensor.getMeasuredPressure() < minPressure && pumpOnTime <= 0)
  {
    if (minPressureCounter >=minPressureDebounceCount)
    {
      pumpOnTime=1;
      pumpOnUnderPressureTime=1;
      minPressureCounter=0;
      relayControl.RelayOn();
    } else {
      statusHandler.showMessage("Low Press wait.");
      minPressureCounter++;
    } 
  } 
  else
  {
    if (relayControl.getRelayIsOn()==false)
    {
      statusHandler.showMessage("Pump Off");
    }
  }
  if (pressureSensor.getMeasuredPressure() < setPressure && pumpOnTime > 0)
  {   
    pumpOnTime++;
    if (pressureSensor.getMeasuredPressure() < minPressure)
    {
      pumpOnUnderPressureTime++;
    } 
    else
    {
      pumpOnUnderPressureTime=0;
    }
  }
  if (pumpOnTime>0)
  {
    if (relayControl.getRelayIsOn()==false)
    {
      if (pumpCooldownCheckTime >= pumpCooldownTime)
      {
        pumpOnTime = 0;
        pumpCooldownCheckTime=0;
        pumpOnUnderPressureTime=0;
        minPressureCounter=0;
      }
      else 
      {
        pumpCooldownCheckTime++;
        statusHandler.showMessage("Pump Cool");
        statusHandler.printTime(1,11,pumpCooldownCheckTime);
      }
    } 
    else
    {
      statusHandler.showMessage("RT-00:00");
      statusHandler.printTime(0,11,pumpOnTime);

      pumpCooldownCheckTime=0; 
    }
  }
  
  
  
}
// the loop function runs over and over again forever
void loop() {
  //
  
  
  digitalWrite(blinkPin, HIGH);   // turn the LED on (shows something is running on board)
  processPressure();
  delay(500);                       // wait for a second
  digitalWrite(blinkPin, LOW);    // turn the LED off (shows something is running on board)
  delay(500);                       // wait for a second
  
}

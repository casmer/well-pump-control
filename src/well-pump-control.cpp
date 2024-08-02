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

#include <ArduinoBLE.h>
#include <Arduino.h>
#include <loopTimer.h>
#include "digital_pin_defs.h"
#include <pins_arduino.h>
#include <RelayControl.h>
#include <StatusHandler.h>
#include <PressureSensor.h>
#include <TemperatureSensor.h>
#include <StateMachine.h>
#include <secrets.h>

////// BEGIN OTA Headers and Variables
#include <WiFiNINA.h>
#include <ArduinoOTA.h>

#include "secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
/////// Wifi Settings ///////
char ssid[] = SECRET_SSID;      // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
int status = WL_IDLE_STATUS;
void printWifiStatus();
void setupOTUpdate();
////// END OTA Headers and Variables

// Configuration
int blinkTime_ms = 1000;
int pressureCheckTime_ms = 200;
int tempSensorCheckTime_ms = 1000;
int statusUpdateTime_ms = 200;
int wifiStatusUpdateDelay_ms = 5000;
// Pin Assignments
uint8_t fanPin = D2;
uint8_t relayPin = D4;
uint8_t blinkPin = D3;
uint8_t pressureSensorPin = A0;
const uint8_t tempSensorSelectPin = D10;

//delay objects
millisDelay ledDelay;
millisDelay pressureCheckDelay;
millisDelay tempSensorReadDelay;
millisDelay statusUpdateDelay;
millisDelay wifiStatusUpdateDelay;

// interface handlers
RelayControl relayControl;
StatusHandler statusHandler;
PressureSensor pressureSensor;
TemperatureSensor temperatureSensor(tempSensorSelectPin, &SPI);
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
  setupOTUpdate();
  statusHandler.setup();
  
  SPI.begin();
  temperatureSensor.setup();
  stateMachine.setup();

  ledDelay.start(blinkTime_ms);
  pressureCheckDelay.start(pressureCheckTime_ms);
  tempSensorReadDelay.start(tempSensorCheckTime_ms);
  statusUpdateDelay.start(statusUpdateTime_ms);
  wifiStatusUpdateDelay.start(wifiStatusUpdateDelay_ms);
  
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

void wifiStatusUpdate()
{
  if (wifiStatusUpdateDelay.justFinished())
  {
    printWifiStatus();
    wifiStatusUpdateDelay.repeat();    
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

void processTemperature()
{
  if (tempSensorReadDelay.justFinished())
  {

    uint8_t result = temperatureSensor.readTemperature();
    if (result == 0)
    {
      statusHandler.updateTemperature(temperatureSensor.getMeasuredTemperature_F());
      Serial.print("Temp:");
      Serial.print(temperatureSensor.getMeasuredTemperature_F(),3);
      Serial.print(" F ");
      Serial.print(temperatureSensor.getMeasuredTemperature(),3);
      Serial.println(" C");
    }
    else
    {
      Serial.print("temp Read Error:");
      Serial.println(static_cast<int>(result));
    }
    tempSensorReadDelay.repeat();
  }
}
void setupOTUpdate()
{
   // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }

  // start the WiFi OTA library with internal (flash) based storage
  ArduinoOTA.begin(WiFi.localIP(), SECRET_UPLOAD_USER, SECRET_UPLOAD_PASSWORD, InternalStorage);

  // you're connected now, so print out the status:
  printWifiStatus();
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
 
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

 
// the loop function runs over and over again forever
void loop() {
  //
  stateMachine.tick();
  
  processPressure();
  processTemperature();
  blinkLed();
  statusUpdate();  
  wifiStatusUpdate();
  // check for WiFi OTA updates
  ArduinoOTA.poll();
  
  delay(250);     //loop time.
}

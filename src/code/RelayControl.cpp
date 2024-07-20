

#include <inttypes.h>
#include "Arduino.h"

#include <RelayControl.h>

void RelayControl::On()
{
  _relayIsOn=true;
  digitalWrite(_relayPin, HIGH);   // relay on
}

void RelayControl::Off()
{
  if (_relayIsOn)
  {
    Serial.println("Relay Off");

  }
  _relayIsOn=false;
  digitalWrite(_relayPin, LOW);   // relay off
}

void RelayControl::setDioPin(int relayPin)
{
    _relayPin = relayPin;
}
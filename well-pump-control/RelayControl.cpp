

#include <inttypes.h>
#include "Arduino.h"

#include "RelayControl.h"

void RelayControl::RelayOn()
{
  _relayIsOn=true;
  digitalWrite(_relayPin, HIGH);   // relay on
}

void RelayControl::RelayOff()
{
  if (_relayIsOn)
  {
    Serial.println("Relay Off");

  }
  _relayIsOn=false;
  digitalWrite(_relayPin, LOW);   // relay off
}

void RelayControl::setRelayPin(int relayPin)
{
    _relayPin = relayPin;
}
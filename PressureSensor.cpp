#include <inttypes.h>
#include "Arduino.h"

#include "PressureSensor.h"

void PressureSensor::setup(int pressureSensorPin)
{
    _pressureSensorPin = pressureSensorPin;
}
void PressureSensor::readPressure()
{
  
  _pressureSensorPinValue = analogRead(_pressureSensorPin);
  
  _measuredPressure = map(_pressureSensorPinValue,_pressureSensorPinat0,_pressureSensorPinat100,0,100);
  if (_lastMeasuredPressure != _measuredPressure)
  {
    _lastMeasuredPressure = _measuredPressure;
    
  }
}
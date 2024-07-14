#include <inttypes.h>
#include "Arduino.h"


//#define PRINT_PRESSURE

#include "PressureSensor.h"

void PressureSensor::setup()
{

  Wire.begin();
  if(!_adc.init()){
    Serial.println("ADS1115 not connected!");
  }

  _adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  _adc.setCompareChannels(ADS1115_COMP_0_GND);
  _adc.setMeasureMode(ADS1115_CONTINUOUS); 
  
}

float PressureSensor::map(float x, float in_min, float in_max, float out_min, float out_max)
  {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

void PressureSensor::readPressure()
{
  _adc.setCompareChannels(ADS1115_COMP_0_GND);
  _pressureSensorVoltageValue = _adc.getResult_mV(); // alternative: getResult_mV for Millivolt
  
  _measuredPressure =static_cast<int>(map(_pressureSensorVoltageValue,_pressureSensorVoltageAt0,_pressureSensorVoltageAt100,0.0f,100.0f));
  
  if (_lastMeasuredPressure != _measuredPressure)
  {
#ifdef PRINT_PRESSURE
    Serial.print("Pressure:");
    Serial.println(_measuredPressure,4);
#endif
    _lastMeasuredPressure = _measuredPressure; 
  }
}
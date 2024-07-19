#include "DebugEnables.h"

#include <inttypes.h>

//#define PRINT_PRESSURE

#include <PressureSensor.h>

#include<ADS1015_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48


PressureSensor::PressureSensor() :
   _adc{ ADS1115_WE(I2C_ADDRESS)}
    {};

void PressureSensor::setup()
{

  Wire.begin();
  #ifdef PRESSURE_SENSOR_DEBUG
  if(!_adc.init()){
    Serial.println("ADS1115 not connected!");
  }
  #endif
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
  _pressureSensorVoltageValue = _adc.getResult_mV(); 
  
  _measuredPressure =static_cast<int>(map(_pressureSensorVoltageValue,_pressureSensor_mV_at_min_psi,_pressureSensor_mV_at_max_psi,_pressureSensor_min_psi,_pressureSensor_max_psi));
  
  if (_lastMeasuredPressure != _measuredPressure)
  {
#ifdef PRINT_PRESSURE
    Serial.print("Pressure:");
    Serial.println(_measuredPressure,4);
#endif
    _lastMeasuredPressure = _measuredPressure; 
  }
}
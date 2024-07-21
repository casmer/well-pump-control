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

#include "DebugEnables.h"
#include <inttypes.h>


#include <PressureSensor.h>

#include<Wire.h>

#define I2C_ADDRESS 0x48

#define PRINT_PRESSURE

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

float PressureSensor::map(float& x, float& in_min, float& in_max, float& out_min, float& out_max)
{
  #ifdef PRINT_MAP
  static float lastx=0;
  if (abs(lastx-x) >= 1.0f)
  {
    lastx = x;
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" in min: ");
    Serial.print(in_min);
    Serial.print(" in max: ");
    Serial.print(in_max);
    Serial.print(" out min: ");
    Serial.print(out_min);
    Serial.print(" out max: ");
    Serial.print(out_max);
    Serial.println("!");
  }
  #endif
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

const float PressureSensor::clamp(const float& val, const float& lo, const float& hi)
{
  return (val < lo) ? lo : (hi < val) ? hi : val;
}

void PressureSensor::readPressure()
{
  _adc.setCompareChannels(ADS1115_COMP_0_GND);
  _pressureSensorVoltageValue = _adc.getResult_mV(); 
  float sensorVoltageClamped = clamp(_pressureSensorVoltageValue,_pressureSensor_mV_at_min_psi, _pressureSensor_mV_at_max_psi );
  float mappedPressure =map(sensorVoltageClamped,_pressureSensor_mV_at_min_psi,_pressureSensor_mV_at_max_psi,_pressureSensor_min_psi,_pressureSensor_max_psi);
  _measuredPressure =static_cast<int>(mappedPressure);
  
  if (_lastMeasuredPressure != _measuredPressure)
  {
#ifdef PRINT_PRESSURE
    Serial.print("Pressure: ");
    Serial.print(_measuredPressure);
    Serial.print(" [");
    Serial.print(mappedPressure, 4);
    Serial.print("] ");
    Serial.print(" mV: ");
    Serial.print(_pressureSensorVoltageValue, 4);
    Serial.print(" [");
    Serial.print(_pressureSensorVoltageValue, 4);
    Serial.println("]");
#endif
    _lastMeasuredPressure = _measuredPressure; 
  }
}
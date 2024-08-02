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

#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H
#include<ADS1015_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48

class ADS1115_WE;

class PressureSensor
{
public:
    PressureSensor();

    virtual void setup();
    virtual void readPressure();
    virtual int getMeasuredPressure() { return _measuredPressure; }

private:
    float map(float& x, float& in_min, float& in_max, float& out_min, float& out_max);
    const float clamp(const float& val, const float& lo, const float& hi);
    ADS1115_WE _adc;



    //TODO: add analog input measurement to positive voltage line, use two Analog inputs to measure value?
    //Sesnor in garage - .5v = 0 PSI, 4.5v=100PSI


    float _pressureSensorVoltageValue = 0.0f;
    // sensor value at max PSI in millvolts
    float _pressureSensor_mV_at_max_psi=4500.0f;
    // sensor value at min PSI in millvolts
    float _pressureSensor_mV_at_min_psi=500.0f;

    // minimum value the presure sensor can measure.
    float _pressureSensor_min_psi=0.0f;
    // maximum value the presure sensor can measure.
    float _pressureSensor_max_psi=150.0f;

    int _measuredPressure = 0;
    int _lastMeasuredPressure = 0;

};

#endif // PRESSURESENSOR_H
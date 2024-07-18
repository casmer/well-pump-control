

#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include<ADS1015_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48



class PressureSensor
{
public:
    PressureSensor() : _measuredPressure(-1) {};

    void setup();
    void readPressure();
    int getMeasuredPressure() { return _measuredPressure; }

private:
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    ADS1115_WE _adc = ADS1115_WE(I2C_ADDRESS);



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
    float _pressureSensor_max_psi=100.0f;

    int _measuredPressure = 0;
    int _lastMeasuredPressure = 0;

};

#endif
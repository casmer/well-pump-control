

#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include<ADS1015_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48



class PressureSensor
{
    public:
        PressureSensor() {};

        void setup();
        void readPressure();
        int getMeasuredPressure() { return _measuredPressure; }

    private:
        float map(float x, float in_min, float in_max, float out_min, float out_max);
        ADS1115_WE _adc = ADS1115_WE(I2C_ADDRESS);
        float _pressureSensorVoltageValue = 0.0f;
        // pressureSensorPin Reading value at simulated 100 PSI (5v)
        float _pressureSensorVoltageAt100=6000.0f;
        // float _pressureSensorVoltageAt100=939.0f;
        // pressureSensorPin Reading value at simulated 0 PSI (about 0v)
        float _pressureSensorVoltageAt0=7.0f;

        int _measuredPressure = 0;
        int _lastMeasuredPressure = 0;

};

#endif
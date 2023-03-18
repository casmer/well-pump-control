

#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H
class PressureSensor
{
    public:
        PressureSensor() {};

        void setup(int pressureSensorPin);
        void readPressure();
        int getMeasuredPressure() { return _measuredPressure; }

    private:
        int _pressureSensorPinValue = 0;
        // pressureSensorPin Reading value at simulated 100 PSI (5v)
        int _pressureSensorPinat100=939;
        // pressureSensorPin Reading value at simulated 0 PSI (about 0v)
        int _pressureSensorPinat0=7;

        int _pressureSensorPin = 0;

        int _measuredPressure = 0;
        int _lastMeasuredPressure = 0;

};

#endif
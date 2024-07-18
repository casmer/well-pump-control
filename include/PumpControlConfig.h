

#ifndef PUMP_CONTROL_CONFIG
#define PUMP_CONTROL_CONFIG


class PumpControlConfig
{

    public:
        int getSetPressureHigh() { return _setPressureHigh; }
        int getSetPressureLow() { return _setPressureLow; }
        int getLowPressureDelay_ms() { return _lowPressureDelay_ms; }

        int getLowPressureError() { return _lowPressureError; }
        int getMaxLowPressureRunTime_ms() { return _maxLowPressureRunTime_ms; }
        static PumpControlConfig instance;
    private:
         int _setPressureHigh = 45;
        int _setPressureLow = 30;
        int _lowPressureDelay_ms = 3000;

        int _lowPressureError = 10;
        int _maxLowPressureRunTime_ms = 60;


};

#define CONFIG() PumpControlConfig::instance

#endif // PUMP_CONTROL_CONFIG
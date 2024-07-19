

#ifndef PUMP_CONTROL_CONFIG
#define PUMP_CONTROL_CONFIG


class PumpControlConfig
{

    public:
        static PumpControlConfig& pumpConifg()
        {
            static PumpControlConfig instance;
            return instance;
        }

        int getSetPressureHigh() { return _setPressureHigh; }
        int getSetPressureLow() { return _setPressureLow; }
        unsigned int getLowPressureDelay_ms() { return _lowPressureDelay_ms; }

        int getLowPressureError() { return _lowPressureError; }
        unsigned int getMaxLowPressureRunTime_ms() { return _maxLowPressureRunTime_ms; }
    private:
        PumpControlConfig() {};
        PumpControlConfig(PumpControlConfig const&);              // Don't Implement
        void operator=(PumpControlConfig const&); // Don't implement

         int _setPressureHigh = 45;
        int _setPressureLow = 30;
        unsigned int _lowPressureDelay_ms = 3000;

        int _lowPressureError = 10;
        unsigned int _maxLowPressureRunTime_ms = 60;


};

#define CONFIG() PumpControlConfig::pumpConifg()

#endif // PUMP_CONTROL_CONFIG
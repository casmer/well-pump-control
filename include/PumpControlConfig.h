

#ifndef PUMP_CONTROL_CONFIG
#define PUMP_CONTROL_CONFIG

/// @brief returns the number of milliseconds in the provided value for minutes
#define MINUTES_ms(minutes) (minutes * 1000 * 60)
/// @brief returns the number of milliseconds in the provided value for seconds
#define SECONDS_ms(seconds) (seconds * 1000)
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
        unsigned int _lowPressureDelay_ms = SECONDS_ms(3);

        int _lowPressureError = 10;
        unsigned int _maxLowPressureRunTime_ms = SECONDS_ms(10);
};

#define CONFIG() PumpControlConfig::pumpConifg()

#endif // PUMP_CONTROL_CONFIG
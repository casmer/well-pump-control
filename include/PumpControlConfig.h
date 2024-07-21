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
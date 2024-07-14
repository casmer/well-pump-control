


#ifndef STATUSHANDLER_H
#define STATUSHANDLER_H
class StatusHandler
{
    public:
        StatusHandler() {};

        void setup();
        void updatePressure(int measuredPressure);
        void printTime(int line, int startPos, int timeInS);
        void showMessage(const char* message);
        int getSetPressureHigh() { return _setPressureHigh; }
        int getSetPressureLow() { return _setPressureLow; }
        int getLowPressureDelay() { return _lowPressureDelay; }

        int getLowPressureError() { return _lowPressureError; }
        int getMaxLowPressureRunTime() { return _maxLowPressureRunTime; }
    private:
        bool _relayIsOn = false;
        int _relayPin = 0;
        int _setPressureHigh = 45;
        int _setPressureLow = 30;
        int _lowPressureDelay = 3;

        int _lowPressureError = 10;
        int _maxLowPressureRunTime = 60;

};

#endif
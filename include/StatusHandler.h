


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
       
    private:
        bool _relayIsOn = false;
        int _relayPin = 0;

};

#endif
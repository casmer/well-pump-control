


#ifndef STATUSHANDLER_H
#define STATUSHANDLER_H

enum class MessageId
{
    NO_MESSAGE = 0,
    PUMP_OFF,
    PUMP_ON,
    LOW_PRESSURE_WAIT,
    PRESSURE_RECOVERY,
    LOW_PRESSURE_ERROR,

};

class StatusHandler
{
    public:
        StatusHandler() {};

        virtual void setup();
        virtual void updatePressure(int measuredPressure);
        virtual void printTime(int line, int startPos, int timeInS);
        virtual void showMessage(MessageId message);
       
    private:
        bool _relayIsOn = false;
        int _relayPin = 0;

};

#endif
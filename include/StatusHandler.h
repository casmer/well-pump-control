


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
        virtual void updateTime(int timeInMs);
        virtual void showMessage(MessageId message);
        virtual void updatePressure(int measuredPressure);
        virtual void updatePumpState(bool running);
        virtual void printAll();
    protected:
        virtual void printPressure();
        virtual void printClock();
        virtual void printPumpState();
        virtual void printTime(int line, int startPos, int timeInS);
        virtual void printMessage();

    private:
        MessageId _lastMessageId = MessageId::NO_MESSAGE;
        MessageId _messageId = MessageId::NO_MESSAGE;
        int _lastPressure = -1;
        int _measuredPressure = 0;
        int _lastTime_s = -1;
        int _currentTime_ms = 0;
        bool _pumpRunning=false;
        bool _lastPumpRunning=true;


};

#endif
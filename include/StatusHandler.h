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
        virtual void updateTemperature(float measuredTemperature);
        virtual void updatePumpState(bool running);
        virtual void printAll();
    protected:
        virtual void printPressure();
        virtual void printTemperature();
        virtual void printClock();
        virtual void printPumpVersion();
        virtual void printTime(int line, int startPos, int timeInS);
        virtual void printMessage();

    private:
        MessageId _lastMessageId = MessageId::NO_MESSAGE;
        MessageId _messageId = MessageId::NO_MESSAGE;
        int _lastPressure = -1;
        int _measuredPressure = 0;
        int _lastTemperature = -1;
        float _measuredTemperature = 0;
        int _lastTime_s = -1;
        int _currentTime_ms = 0;
        bool _pumpRunning=false;
        bool _lastPumpRunning=true;


};

#endif
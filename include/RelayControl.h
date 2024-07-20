
#ifndef RELAYCONTROL_H
#define RELAYCONTROL_H
class RelayControl
{
    public:
        RelayControl() {};

        virtual void setDioPin(int relayPin);
        virtual void On();
        virtual void Off();
        virtual bool isOn() { return _relayIsOn; };
    private:
        bool _relayIsOn = false;
        int _relayPin = 0;
};

#endif
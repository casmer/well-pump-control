
#ifndef RELAYCONTROL_H
#define RELAYCONTROL_H
class RelayControl
{
    public:
        RelayControl() {};

        virtual void setRelayPin(int relayPin);
        virtual void RelayOn();
        virtual void RelayOff();
        virtual bool getRelayIsOn() { return _relayIsOn; };
    private:
        bool _relayIsOn = false;
        int _relayPin = 0;

};

#endif
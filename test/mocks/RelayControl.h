
#ifndef RELAYCONTROL_H
#define RELAYCONTROL_H
class RelayControl
{
    public:
        RelayControl() {};

        void setRelayPin(int relayPin);
        void RelayOn();
        void RelayOff();
        bool getRelayIsOn() { return _relayIsOn; };
    private:
        bool _relayIsOn = false;
        int _relayPin = 0;

};

#endif
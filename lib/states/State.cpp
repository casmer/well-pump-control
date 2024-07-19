
#include "State.h"
#include <Arduino.h>

void State::enter()
{
    _state_entry_time=millis();
    enterState();
}

unsigned long State::get_state_time_ms()
{
    return millis() - _state_entry_time;
}
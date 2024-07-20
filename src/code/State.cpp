
#include <State.h>
#include <Arduino.h>

void State::enter()
{
    _state_entry_time=millis();
    _last_state_time = _state_entry_time;
    enterState();
}

unsigned long State::get_state_time_ms()
{
    _last_state_time = millis() - _state_entry_time;
    return _last_state_time;
}

unsigned long State::get_last_state_time_ms()
{
    return _last_state_time;
}
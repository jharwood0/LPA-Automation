/*
  Fogger.h - component of Fogponics library.
  Created by Josh Harwood, October 20, 2018.
*/
#include "Arduino.h"
#include "Fogger.h"

Fogger::Fogger(){

}

Fogger::Fogger(uint8_t pin, uint32_t on_time, uint32_t off_time){
    _fogger_pin = pin;
    _fogger_on_time = on_time;
    _fogger_off_time = off_time;
}

// |----------INTERVAL----------|---DURATION---|----------INTERVAL----------|----DURATION---|
void Fogger::run(unsigned long current_time){
    if (_fogger_state == _fogger_off_state && (current_time - _previous_run >= _fogger_off_time)) {
        if(_debug) _debug_stream->println("[Fogger] activating");
        _fogger_state = _fogger_on_state;
        _fogger_start_time = current_time;
        _previous_run = current_time;
        digitalWrite(_fogger_pin, _fogger_state);
    }
    else if(_fogger_state == _fogger_on_state && (current_time - _fogger_start_time >= _fogger_on_time))
    {
        if(_debug) _debug_stream->println("[Fogger] deactivating");
        _fogger_state = _fogger_off_state;
        digitalWrite(_fogger_pin, _fogger_state);
    }
}

void Fogger::set_states(uint8_t on_state, uint8_t off_state){
    _fogger_on_state = on_state;
    _fogger_off_state = off_state;
}

void Fogger::add_debug(Stream& serial){
    _debug_stream = &serial;
    _debug = 0x01;
}
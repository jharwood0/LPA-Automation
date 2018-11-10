/*
  Timmr.cpp - controller of Fogponics library.
  Created by Josh Harwood, October 20, 2018.
*/
#include "Arduino.h"
#include "Timer.h"

Timer::Timer(){

}

Timer::Timer(Fogponics& fogger_system, uint32_t on_time, uint32_t off_time){
    _fogger_system = &fogger_system;
    _fogger_on_time = on_time;
    _fogger_off_time = off_time;
}


// |----------INTERVAL----------|---DURATION---|----------INTERVAL----------|----DURATION---|
void Timer::run(){
    unsigned long current_time = millis();
    _fogger_state = _fogger_system->get_current_state();
    if(_fogger_state){
        if(_debug) _debug_stream->println("[Fogger] activating");
        _fogger_state = _fogger_on_state;
        _fogger_start_time = current_time;
        _previous_run = current_time;
        digitalWrite(_fogger_pin, _fogger_state);
    } else if(_fogger_state == _fogger_on_state && (current_time - _fogger_start_time >= _fogger_on_time)) {
        if(_debug) _debug_stream->println("[Fogger] deactivating");
        _fogger_state = _fogger_off_state;
        digitalWrite(_fogger_pin, _fogger_state);
    }
}

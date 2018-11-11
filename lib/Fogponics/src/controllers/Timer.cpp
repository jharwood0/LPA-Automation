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

void Timer::add_debug(Stream& debug_stream){
    _debug_stream = &debug_stream;
    _debug = 0x01;
    _debug_stream->println("[Timer] enabled debugging");
}

// |----------INTERVAL----------|---DURATION---|----------INTERVAL----------|----DURATION---|
void Timer::run(){
    unsigned long current_time = millis();
    _fogger_state = _fogger_system->get_current_state();
    if(_debug){
         _debug_stream->print("[Timer] fogger state is " + _fogger_state);
         _debug_stream->println(_fogger_state);
    }

    if (_fogger_state == 0 && (current_time - _previous_run >= _fogger_off_time)) {
        if(_debug) _debug_stream->println("[Timer] starting foggers");
        _fogger_system->activate();
        _fogger_start_time = current_time;
        _previous_run = current_time;
    } else if(_fogger_state == 1 && (current_time - _fogger_start_time >= _fogger_on_time)) {
        if(_debug) _debug_stream->println("[Timer] stopping foggers");
        _fogger_system->deactivate();
    }
}

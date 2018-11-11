/*
  Fogponics.cpp - Library for automating ultrasonic based aeroponic systems.
  Created by Josh Harwood, October 20, 2018.
*/
#include "Arduino.h"
#include "Fogponics.h"

Fogponics::Fogponics(){
    _current_state = 0;
}

void Fogponics::add_debug(Stream& debug_stream){
    _debug_stream = &debug_stream;
    _debug = 0x01;
    _debug_stream->println("[Fogponics] enabled debugging");
}

void Fogponics::add_fogger(uint8_t pin){
    Fogger temp(pin);
    _foggers[_num_foggers] = temp;
    if(_debug){
        _debug_stream->print("[Fogponics] attaching fogger at pin ");
        _debug_stream->println(pin);
        _foggers[_num_foggers].add_debug(*_debug_stream);
    }
    _num_foggers++;
}

uint8_t Fogponics::get_current_state(){
    return _current_state;
}

void Fogponics::activate(){
    _current_state = 1;
    for(int i = 0; i < _num_foggers; i++){
        if(_debug) _debug_stream->println("[Fogponics] starting foggers");
        _foggers[i].start();
    }
}

void Fogponics::deactivate(){
    _current_state = 0;
    for(int i = 0; i < _num_foggers; i++){
        if(_debug) _debug_stream->println("[Fogponics] stopping foggers");
        _foggers[i].stop();
    }
}
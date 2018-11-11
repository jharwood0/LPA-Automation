/*
  Fogger.cpp - component of Fogponics library.
  Created by Josh Harwood, October 20, 2018.
*/
#include "Arduino.h"
#include "Fogger.h"

Fogger::Fogger(){

}

Fogger::Fogger(uint8_t pin){
    _fogger_pin = pin;
    pinMode(_fogger_pin, OUTPUT);
}

void Fogger::set_states(uint8_t on_state, uint8_t off_state){
    _fogger_on_state = on_state;
    _fogger_off_state = off_state;
}

void Fogger::add_debug(Stream& serial){
    _debug_stream = &serial;
    _debug_stream->println("[Fogger] enabled debugging");
    _debug = 0x01;
}

void Fogger::start(){
    if(_debug) _debug_stream->println("[Fogger] started fogger");
    _fogger_state = _fogger_on_state;
    digitalWrite(_fogger_pin, _fogger_state);
}

void Fogger::stop(){
    if(_debug) _debug_stream->println("[Fogger] stopped fogger");
    _fogger_state = _fogger_off_state;
    digitalWrite(_fogger_pin, _fogger_state);
}

uint8_t Fogger::get_current_state(){
    return _fogger_state;
}
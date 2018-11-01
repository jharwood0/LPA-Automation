/*
  Fogponics.cpp - Library for automating ultrasonic based aeroponic systems.
  Created by Josh Harwood, October 20, 2018.
*/
#include "Arduino.h"
#include "Fogponics.h"

Fogponics::Fogponics(){
}

void Fogponics::add_debug(Stream& debug_stream){
    this->_debug_stream = &debug_stream;
    this->_debug = 0x01;
    this->_debug_stream->println("Loaded fogponics systems");
}

void Fogponics::add_fogger(uint8_t pin, uint8_t on_state, uint32_t on_time, uint32_t off_time){
    Fogger temp(pin, on_time, off_time);
    this->_foggers[_num_foggers] = temp;
    if(_debug){
        this->_foggers[_num_foggers].add_debug(*_debug_stream);
    }
}

void Fogponics::run(){
    unsigned long current_time = millis();
    for(int i = 0; i < _num_foggers; i++){
        this->_foggers[i].run(current_time);
    }
}
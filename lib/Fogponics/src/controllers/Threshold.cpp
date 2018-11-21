/*
  Timmr.cpp - controller of Fogponics library.
  Created by Josh Harwood, October 20, 2018.
*/
#include "Arduino.h"
#include "Threshold.h"

Threshold::Threshold(){

}

Threshold::Threshold(Fogponics& fogger_system, DHT& sensor, uint8_t humidity, uint8_t min_humidity, uint8_t max_humidity){
    _fogger_system = &fogger_system;
    _sensor = &sensor;
    _humidity = humidity;
    _min_humidity = min_humidity;
    _max_humidity = max_humidity;
}

void Threshold::add_debug(Stream& debug_stream){
    _debug_stream = &debug_stream;
    _debug = 0x01;
    _debug_stream->println("[Threshold] enabled debugging");
}

void Threshold::run(){
    
}

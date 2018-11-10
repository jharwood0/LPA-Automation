/*
  Fogponics.h - Library for automating ultrasonic based aeroponic systems.
  Created by Josh Harwood, October 20, 2018.
*/
#ifndef Fogponics_h
#define Fogponics_h

#include "Arduino.h"
#include "./components/Fogger.h"

class Fogponics
{
  public:
    Fogponics();
    void add_fogger(uint8_t pin, uint8_t state, uint32_t on_time, uint32_t off_time);
    void add_debug(Stream& debug_stream);
    uint8_t get_current_state();
    void run();
    void activate();
    void deactivate(); 
  private:
    Fogger _foggers[10];
    uint8_t _num_foggers = 0;
    Stream* _debug_stream;
    uint8_t _debug;
    uint8_t _current_state;
};

#endif
/*
  Timer.h - controller of Fogponics library.
  Created by Josh Harwood, October 20, 2018.
*/
#ifndef Timer_h
#define Timer_h

#include "Arduino.h"
#include "../Fogponics.h"

class Timer
{
  public:
    Timer();
    Timer(Fogponics& fogger_system, uint32_t on_time, uint32_t off_time);
    void run();
    void add_debug(Stream& debug_stream);
  private:
    unsigned long _previous_run;
    uint8_t _fogger_pin;
    uint8_t _fogger_on_state = HIGH;
    uint8_t _fogger_off_state = LOW;
    volatile uint8_t _fogger_state;
    uint32_t _fogger_on_time, _fogger_off_time;
    unsigned long _fogger_start_time;
    Stream* _debug_stream;
    uint8_t _debug;
    Fogponics* _fogger_system;
};

#endif
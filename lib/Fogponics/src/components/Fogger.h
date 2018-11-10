/*
  Fogger.h - component of Fogponics library.
  Created by Josh Harwood, October 20, 2018.
*/
#ifndef Fogger_h
#define Fogger_h

#include "Arduino.h"

class Fogger
{
  public:
    Fogger();
    Fogger(uint8_t pin);
    //Fogger(uint8_t pin, uint32_t on_time, uint32_t off_time);
    //void run(unsigned long current_time);
    void start();
    void stop();
    void set_states(uint8_t on_state, uint8_t off_state);
    void add_debug(Stream& debug);
    uint8_t get_current_state();
  private:
    unsigned long _previous_run;
    uint8_t _fogger_pin;
    uint8_t _fogger_on_state = HIGH;
    uint8_t _fogger_off_state = LOW;
    volatile uint8_t _fogger_state;
    //uint32_t _fogger_on_time, _fogger_off_time;
    //unsigned long _fogger_start_time;
    Stream* _debug_stream;
    uint8_t _debug;
};

#endif
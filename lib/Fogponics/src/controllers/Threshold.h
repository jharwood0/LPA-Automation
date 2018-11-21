/*
  Threshold.h - controller of Fogponics library.
  Created by Josh Harwood, October 20, 2018.
*/
#ifndef Threshold_h
#define Threshold_h

#include "Arduino.h"
#include "DHT.h"
#include "../Fogponics.h"

class Threshold
{
  public:
    Threshold();
    Threshold(Fogponics& fogger_system, DHT& sensor, uint8_t humidity, uint8_t min_humidity, uint8_t max_humidity);
    void run();
    void add_debug(Stream& debug_stream);
  private:
    Stream* _debug_stream;
    uint8_t _debug;
    Fogponics* _fogger_system;
    DHT* _sensor;
    uint8_t _humidity;
    uint8_t _min_humidity;
    uint8_t _max_humidity;
};

#endif
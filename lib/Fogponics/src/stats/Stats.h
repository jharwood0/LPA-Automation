/*
  Stats.h - statistics aggregator for Fogponics library.
  Created by Josh Harwood, November 21, 2018.
*/
#ifndef Stats_h
#define Stats_h

#include "Arduino.h"
#include "HTTPClient.h"
#include "../Fogponics.h"


class Stats
{
  public:
    Stats();
    Stats(char* stats_endpoint, HTTPClient& http, Fogponics& fogger_system, uint32_t interval);
    void handle();
    void add_debug(Stream& debug_stream);
  private:
    unsigned long _previous_run;
    char* _stats_endpoint;
    uint32_t _interval;
    Stream* _debug_stream;
    uint8_t _debug;
    Fogponics* _fogger_system;
    HTTPClient* _http;
    struct content {
        uint8_t id;
        uint8_t status;
    };
    char* createPayload(content data);
    int tx(char* payload);
};

#endif
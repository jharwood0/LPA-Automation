/*
  Stats.cpp - controller of Fogponics library.
  Created by Josh Harwood, October 20, 2018.
*/
#include "Arduino.h"
#include "Stats.h"

Stats::Stats(){

}

Stats::Stats(char* stats_endpoint, HTTPClient& http, Fogponics& fogger_system, uint32_t interval){
    _stats_endpoint = stats_endpoint;
    _interval = interval;
    _http = &http;
    _fogger_system = &fogger_system;
}

void Stats::add_debug(Stream& debug_stream){
    _debug_stream = &debug_stream;
    _debug = 0x01;
    _debug_stream->println("[Stats] enabled debugging");
}

char* Stats::createPayload(content data){
    char* test;
    sprintf(test, "{Id: %d, Status: %d}", data.id, data.status);
    return test;
}

int Stats::tx(char* payload){
    _http->begin(_stats_endpoint);
    _http->addHeader("Content-Type", "application/json");
    return _http->POST("{name:'test'}");
}

void Stats::handle(){
    unsigned long current = millis();
    if(current - _previous_run >= _interval){
        _previous_run = current;
        content data;
        data.id = 0;
        data.status = _fogger_system->get_current_state();
        char* test = createPayload(data);
        tx(test);
    }
}

#include <Arduino.h>
#include <Fogponics.h>
#include <controllers/Timer.h>

Fogponics sys;
Timer timerController(sys, 5000, 60000);
void setup() {
    Serial.begin(9600);
    sys.add_debug(Serial);
    sys.add_fogger(3, LOW, 5000, 60000);
}

void loop() {
    timerController.run(); 
    delay(500);
}
#include <Arduino.h>
#include <Fogponics.h>
#include <controllers/Timer.h>

Fogponics sys;
Timer timerController(sys, 5000, 60000);
void setup() {
    Serial.begin(9600);
    while (!Serial){
    ;
    }
    Serial.println("Starting system");
    sys.add_debug(Serial);
    sys.add_fogger(4);
    timerController.add_debug(Serial);
}

void loop() {
    timerController.run(); 
    delay(500);
}

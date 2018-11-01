#include <Arduino.h>
#include <Fogponics.h>

Fogponics sys;
void setup() {
    Serial.begin(9600);
    sys.add_debug(Serial);
    sys.add_fogger(3, LOW, 5000, 60000);
}

void loop() {
    sys.run(); 
    delay(500);
}
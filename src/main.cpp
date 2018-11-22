#include <Arduino.h>
#include <Fogponics.h>
#include <controllers/Timer.h>

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <InfluxArduino.hpp>

const char* ssid = "";
const char* password = "";
const char* influx_db = "";
const char* influx_ip = "";
const uint16_t influx_port = 8086;

Fogponics sys;
Timer timerController(sys, 5000, 60000);
InfluxArduino influx;
void setup() {
    Serial.begin(9600);
    while (!Serial){
    ;
    } 
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    ArduinoOTA.setHostname("esp32_basil");

    Serial.println("Starting system");
    sys.add_debug(Serial);
    sys.add_fogger(4);
    timerController.add_debug(Serial);
    influx.configure(influx_db, influx_ip, influx_port);

    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    ArduinoOTA.begin();
}

void handle_stats(){
  char tags[32];
  sprintf(tags,"id=0"); //write a tag called new_tag
  char fields[32];
  sprintf(fields,"status=%d",sys.get_current_state()); //write two fields: id and state
  uint8_t writeSuccessful = influx.write("fogponics",tags,fields);
  if(!writeSuccessful)
  {
    Serial.print("error: ");
    Serial.println(influx.getResponse());
  }
}

void loop() {
    timerController.run();
    ArduinoOTA.handle();
    handle_stats();
    delay(500);
}

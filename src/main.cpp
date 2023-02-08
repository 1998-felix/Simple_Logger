#include <Arduino.h>
#include <WiFi.h>

#include "simple_logger.h"
#include "Credentials.h"

// function prototypes
void connnectWiFi();
// objects
Logger mylogger;

void setup() {
  Serial.begin(115200);
  connnectWiFi();
  mylogger.init();
  
}

void loop() {
  Serial.println(mylogger.logg("Hello, World!"));
  delay(1000);
  
}

void connnectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf("Attempting to connect to: %s \n", credentials.ssid);
    WiFi.begin(credentials.ssid, credentials.password);
    delay(3000);
    if (WiFi.status() == WL_IDLE_STATUS) {
      Serial.println("Attempting connection. Device Idle ");
    }
  }
  Serial.println("Wifi connected succesfully!!!!!");
}
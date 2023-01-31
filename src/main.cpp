#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

#include <string>

#include "Credentials.h"

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 10800;
const int daylightOffset_sec = 0;

String logParser(String text);

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%b %d %Y %H: %M: %S");
  Serial.printf("%d,%d,%d,%d, %d, %d", timeinfo.tm_year, timeinfo.tm_mon,
                timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min,
                timeinfo.tm_sec);
}
void scanNetworks() {
  Serial.println(".................");
  Serial.println("Scanning networks");
  Serial.println(".................");
  byte num_ssid = WiFi.scanNetworks();
  for (int i = 0; i < num_ssid; i++) {
    Serial.print("Network # ");
    Serial.printf(" %d ", i);
    Serial.println(WiFi.SSID(i));
  }
  Serial.println(".................");
  Serial.println("Scan complete....");
  Serial.println("..................");
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
void displayWiFiDetails() {
  long rssi = WiFi.RSSI();
  IPAddress ip;
  ip = WiFi.localIP();
  Serial.print("Wifi Network: ");
  Serial.print(credentials.ssid);
  Serial.print(" RSSI : ");
  Serial.print(rssi);
  Serial.println(" dbm");
  Serial.print("Device Ip Address: ");
  Serial.println(ip);
}

struct tm client_time;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // WiFi
  scanNetworks();
  connnectWiFi();
  displayWiFiDetails();

  // init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  // printLocalTime();
  while (!getLocalTime(&client_time)) {
    Serial.println("Failed to obtain time");
    delay(10);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(300);
  Serial.println(logParser("Hello, World"));
}
void logParser_init(void) {}
String logParser(String text) {
  if(!getLocalTime(&client_time)){
    return text;
  }
  String log_year_str = (String)(client_time.tm_year + 1900);
  int log_month = client_time.tm_mon + 1;
  int log_day = client_time.tm_mday;
  int log_hour = client_time.tm_hour;
  int log_min = client_time.tm_min;
  int log_sec = client_time.tm_sec;
  String log_month_str;
  if (log_month < 10) {
    log_month_str = "0" + String(log_month);
  } else
    log_month_str = String(log_month);

  String log_day_str;
  if (log_day < 10) {
    log_day_str = "0" + String(log_day);
  } else
    log_day_str = String(log_day);
  String log_hour_str;
  if (log_hour < 10) {
    log_hour_str = "0" + String(log_hour);
  } else
    log_hour_str = String(log_hour);
  String log_min_str;
  if (log_min < 10) {
    log_min_str = "0" + String(log_min);
  } else
    log_min_str = String(log_min);
  String log_sec_str;
  if (log_sec < 10) {
    log_sec_str = "0" + String(log_sec);
  } else
    log_sec_str = String(log_sec);

  String log_text = log_year_str + "-" + log_month_str + "-" + log_day_str +
                    " " + log_hour_str + ":" + log_min_str + ":" + log_sec_str;

  return log_text + " " + text;
}
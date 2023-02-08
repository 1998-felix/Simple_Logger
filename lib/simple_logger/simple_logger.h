#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H

#include <Arduino.h>
#include <time.h>

#include <string>

struct {
  const char* ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 10800;
  const int daylightOffset_sec = 0;

} ntp_time_const;

class Logger {
 public:
  Logger(void);
  void init(void);
  String logg(String text);

 private:
  struct tm client_time;

};

#endif
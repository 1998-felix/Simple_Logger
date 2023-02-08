#include "simple_logger.h"

Logger::Logger(void) {}

void Logger::init(void) {
  configTime(ntp_time_const.gmtOffset_sec, ntp_time_const.daylightOffset_sec,
             ntp_time_const.ntpServer);
  while (!getLocalTime(&client_time)) {
    // Serial.println("Failed to obtain time");
    delay(10);
  }
}
String Logger::logg(String text) {
  if (!getLocalTime(&client_time)) {
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
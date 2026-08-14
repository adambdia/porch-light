#include "Schedule.h"
#include "APIClient.h"
#include "Light.h"
#include "esp32-hal.h"
#include <Arduino.h>
#include <cstdint>
#include <ctime>
#include <time.h>

static const char *tz_info = "EST5EDT,M3.2.0,M11.1.0";
static time_t sunset = 0;
static time_t sunrise = 0;
static time_t syncTime = 0;
static const uint32_t SCHEDULE_LOOP_INTERVAL = 1000;
static uint32_t lastRunTime = 0;

void updateSchedule() { fetchSunTimes(&sunrise, &sunset); }

time_t getNextSyncTime(time_t now) {
  // convert unix epoch to broken down time
  struct tm *timeinfo = localtime(&now);

  // next day, 10 minutes past midnight
  timeinfo->tm_mday += 1;
  timeinfo->tm_hour = 0;
  timeinfo->tm_min = 10;
  timeinfo->tm_sec = 0;

  // converts the broken down time to unix time
  return mktime(timeinfo);
}

// config time and wait for first sync
void initSchedule() {
  configTzTime(tz_info, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 1000000000) {
    delay(500);
    now = time(nullptr);
  }

  updateSchedule();
  getNextSyncTime(now);
}

void loopSchedule() {
  if (millis() - lastRunTime < SCHEDULE_LOOP_INTERVAL)
    return;

  time_t now = time(nullptr); // current time in unix time

  if (now > syncTime) {
    updateSchedule();
    getNextSyncTime(now);
  }

  if (now < sunrise) {
    scheduleLightOn();
  } else if ((now > sunrise) && (now < sunset)) {
    scheduleLightOff();
  } else if (now > sunset) {
    scheduleLightOn();
  }

  lastRunTime = millis();
}

#include "Schedule.h"
#include "APIClient.h"
#include "Light.h"
#include <Arduino.h>
#include <cstdint>
#include <ctime>
#include <time.h>

static const char *tz_info = "EST5EDT,M3.2.0,M11.1.0";

static time_t turnOffTime = 0;
static time_t turnOnTime = 0;
static bool useSunrise = true;
static bool useSunset = true;

static int tomorrowOffHour = 0;
static int tomorrowOffMinute = 0;
static int tomorrowOffSecond = 0;

static int tomorrowOnHour = 0;
static int tomorrowOnMinute = 0;
static int tomorrowOnSecond = 0;

static time_t syncTime = 0;
static const uint32_t SCHEDULE_LOOP_INTERVAL = 1000;
static uint32_t lastRunTime = 0;

// might not set on/off time to follow sunset, this accounts for that
void updateSchedule(time_t now) {
  time_t sunrise;
  time_t sunset;

  if (useSunset || useSunset)
    fetchSunTimes(&sunrise, &sunset);

  if (useSunrise)
    turnOffTime = sunrise;
  else
    turnOffTime = getTomorrowAt(now, tomorrowOffHour, tomorrowOffMinute,
                                tomorrowOffSecond);

  if (useSunset)
    turnOnTime = sunset;
  else
    turnOnTime =
        getTomorrowAt(now, tomorrowOnHour, tomorrowOnMinute, tomorrowOnSecond);
}

// helper function to get a timestamp the next day at a certain
// hour:minute:second
time_t getTomorrowAt(time_t base, int hour, int minute, int second) {
  // convert unix epoch to broken down time
  struct tm *timeinfo = localtime(&base);

  // next day plus offsets
  timeinfo->tm_mday += 1;
  timeinfo->tm_hour = hour;
  timeinfo->tm_min = minute;
  timeinfo->tm_sec = second;

  // converts the broken down time to unix time
  return mktime(timeinfo);
}

void getNextSyncTime(time_t now) {
  // next day, 10 minutes past midnight
  syncTime = getTomorrowAt(now, 0, 10, 0);
}

// config time and wait for first sync
void initSchedule() {
  configTzTime(tz_info, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 1000000000) {
    delay(500);
    now = time(nullptr);
  }

  updateSchedule(now);
  getNextSyncTime(now);
}

void loopSchedule() {
  // no reason to check faster than the clock updates
  if (millis() - lastRunTime < SCHEDULE_LOOP_INTERVAL)
    return;

  time_t now = time(nullptr); // current time in unix time

  if (now > syncTime) {
    updateSchedule(now);
    getNextSyncTime(now);
  }

  if (now < turnOffTime) {
    scheduleLightOn();
  } else if ((now > turnOffTime) && (now < turnOnTime)) {
    scheduleLightOff();
  } else if (now > turnOnTime) {
    scheduleLightOn();
  }

  lastRunTime = millis();
}

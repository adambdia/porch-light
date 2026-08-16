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

static int tomorrowOnHour = 0;
static int tomorrowOnMinute = 0;

static time_t syncTime = 0;
static const uint32_t SCHEDULE_LOOP_INTERVAL = 1000;
static uint32_t lastRunTime = 0;

// might not set on/off time to follow sunset, this accounts for that
void updateSchedule() {
  time_t sunrise;
  time_t sunset;
  time_t now = time(nullptr); // current time in unix time

  if (useSunset || useSunrise)
    fetchSunTimes(&sunrise, &sunset);

  if (useSunrise)
    turnOffTime = sunrise;
  else
    turnOffTime = getNextOccurence(now, tomorrowOffHour, tomorrowOffMinute);

  if (useSunset)
    turnOnTime = sunset;
  else
    turnOnTime = getNextOccurence(now, tomorrowOnHour, tomorrowOnMinute);
}

void updateScheduleFromWeb(struct tm onTime, struct tm offTime,
                           bool form_useSunrise, bool form_useSunset) {
  useSunrise = form_useSunrise;
  useSunset = form_useSunset;

  tomorrowOnHour = onTime.tm_hour;
  tomorrowOnMinute = onTime.tm_min;

  tomorrowOffHour = offTime.tm_hour;
  tomorrowOffMinute = offTime.tm_min;

  // immediately update schedule, don't wait for next sync time
  updateSchedule();
}

// helper function to get a timestamp of the next  at a certain
// hour:minute:second
time_t getNextOccurence(time_t base, int hour, int minute) {
  // convert unix epoch to broken down time
  struct tm timeinfo;
  localtime_r(&base, &timeinfo);

  // next day plus offsets
  timeinfo.tm_hour = hour;
  timeinfo.tm_min = minute;
  timeinfo.tm_sec = 0;

  time_t target_today = mktime(&timeinfo);

  if (target_today <= base) {
    timeinfo.tm_mday += 1;
    return mktime(&timeinfo);
  }

  return target_today;
}

void getNextSyncTime(time_t now) {
  // next day, 10 minutes past midnight
  syncTime = getNextOccurence(now, 0, 10);
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
  // no reason to check faster than the clock updates
  if (millis() - lastRunTime < SCHEDULE_LOOP_INTERVAL)
    return;

  time_t now = time(nullptr); // current time in unix time

  if (now > syncTime) {
    updateSchedule();
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

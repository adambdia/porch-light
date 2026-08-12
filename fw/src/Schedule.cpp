#include "Schedule.h"
#include <Arduino.h>
#include <time.h>

static const char *tz_info = "EST5EDT,M3.2.0,M11.1.0"; // EST

// config time and wait for first sync
void initSchedule() {
  configTzTime(tz_info, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 1000000000) {
    delay(500);
    now = time(nullptr);
  }
}

void loopSchedule() {}

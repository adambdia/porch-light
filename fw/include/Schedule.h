#include <time.h>

#ifndef SCHEDULE_H
#define SCHEDULE_H

void initSchedule();
time_t getTomorrowAt(time_t base, int hour, int minute, int second);
void loopSchedule();

#endif

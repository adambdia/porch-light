#include <time.h>

#ifndef SCHEDULE_H
#define SCHEDULE_H

void initSchedule();
time_t getNextOccurence(time_t base, int hour, int minute);
void updateScheduleFromWeb(struct tm onTime, struct tm offTime, bool useSunrise,
                           bool useSunset);
void loopSchedule();

#endif

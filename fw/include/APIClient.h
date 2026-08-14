#include <time.h>

#ifndef APICLIENT_H
#define APICLIENT_H

void initAPIClient();
void fetchSunTimes(time_t *sunrise, time_t *sunset);

#endif

#include <Arduino.h>

#ifndef LIGHT_H
#define LIGHT_H

typedef enum { LIGHT_ON, LIGHT_OFF } light_state_t;

void initLight();
void turnOnLight();
void turnOffLight();
void setLightState(light_state_t state);
void loopLight();

#endif

#include <Arduino.h>
#include <cstdint>

#ifndef LIGHT_H
#define LIGHT_H

void initLight();

// to be handled by scheduler
void scheduleLightOn();
void scheduleLightOff();

// webpage button or physical button
void overrideLight();
void disableOverrideLight();
bool getLightOverride();
void setOverrideDuration(uint32_t duration);

void loopLight();

#endif

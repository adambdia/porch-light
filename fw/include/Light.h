#include <Arduino.h>

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

void loopLight();

#endif

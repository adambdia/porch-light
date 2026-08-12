#include "Light.h"
#include <Arduino.h>

static int relayPin = 8;
static bool scheduleLightEnabled = false;
static const time_t LIGHT_OVERRIDE_DURATION = 10 * 1000; // 10 seconds for now
static volatile time_t lightOverrideExpireTime = 0;
static volatile bool lightOverrideEnabled = false;

void initLight() { pinMode(relayPin, OUTPUT); }

void turnOnLight() { digitalWrite(relayPin, HIGH); }

void turnOffLight() { digitalWrite(relayPin, LOW); }

// void toggleLight() {
//   if (current_light_state == LIGHT_ON)
//     next_light_state = LIGHT_OFF;
//   else
//     next_light_state = LIGHT_ON;
// }

// these functions will eventually be called in Schedule.cpp
void scheduleLightOn() { lightOverrideEnabled = true; }

void scheduleLightOff() { lightOverrideEnabled = false; }

void overrideLight() {
  lightOverrideEnabled = true;
  lightOverrideExpireTime = millis() + LIGHT_OVERRIDE_DURATION;
}

void disableOverrideLight() {
  lightOverrideEnabled = false;
  lightOverrideExpireTime = 0;
}

bool getLightOverride() { return lightOverrideEnabled; }

bool getLightSchedule() { return scheduleLightEnabled; }

void updateOverrideTimer() {
  if (millis() > lightOverrideExpireTime) {
    disableOverrideLight();
  }
}

void loopLight() {
  updateOverrideTimer();
  bool overrideActive = getLightOverride();
  bool scheduleActive = getLightSchedule();
  // The concensus, turn on the light if one or the other is on
  bool decision = overrideActive || scheduleActive;

  if (decision)
    turnOnLight();
  else
    turnOffLight();
}

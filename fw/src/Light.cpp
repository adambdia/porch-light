#include "Light.h"
#include "esp32-hal.h"
#include <Arduino.h>
#include <cstdint>

static int relayPin = 8;
static volatile bool scheduleLightEnabled = false;
static const time_t LIGHT_OVERRIDE_DURATION = 10 * 1000; // 10 seconds for now
static volatile time_t lightOverrideExpireTime = 0;
static volatile bool lightOverrideEnabled = false;
static volatile uint32_t lastLightOverride = 0;

void initLight() { pinMode(relayPin, OUTPUT); }

void turnOnLight() { digitalWrite(relayPin, HIGH); }

void turnOffLight() { digitalWrite(relayPin, LOW); }

// these functions will eventually be called in Schedule.cpp
void scheduleLightOn() { scheduleLightEnabled = true; }
void scheduleLightOff() { scheduleLightEnabled = false; }

void overrideLight() {
  lightOverrideEnabled = true;
  lastLightOverride = millis();
}

void disableOverrideLight() { lightOverrideEnabled = false; }

bool getLightOverride() { return lightOverrideEnabled; }

bool getLightSchedule() { return scheduleLightEnabled; }

void updateOverrideTimer() {
  if (millis() - lastLightOverride > LIGHT_OVERRIDE_DURATION) {
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

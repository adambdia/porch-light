#include "Light.h"
#include <Arduino.h>

static int relayPin = 10;
static light_state_t current_light_state = LIGHT_OFF;
static light_state_t next_light_state = LIGHT_OFF;

void initLight() { pinMode(relayPin, OUTPUT); }

void turnOnLight() {
  digitalWrite(relayPin, HIGH);
  current_light_state = LIGHT_ON;
}

void turnOffLight() {
  digitalWrite(relayPin, LOW);
  current_light_state = LIGHT_OFF;
}

void setLightState(light_state_t state) { next_light_state = state; }

void loopLight() {
  if (current_light_state != next_light_state) {
    if (next_light_state == LIGHT_ON)
      turnOnLight();
    else
      turnOffLight();
  }
}

#include "Button.h"
#include "Light.h"
#include "esp32-hal-gpio.h"
#include <Arduino.h>
#include <cstdint>

static const int buttonPin = 0;
static const int BUTTON_ON = 0; // active low
static const int BUTTON_OFF = 1;
static const uint32_t BUTTON_DEBOUNCE_DURATION = 50; // 50 ms debounce
static uint32_t lastButtonPress = 0;

void initButton() { pinMode(buttonPin, INPUT_PULLUP); }

void loopButton() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == BUTTON_ON) {
    if (millis() - lastButtonPress <= BUTTON_DEBOUNCE_DURATION)
      return;

    overrideLight();
  }
}

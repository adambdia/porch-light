#include "WebHandlers.h"
#include <Arduino.h>

extern volatile bool LEDOn;
extern volatile time_t turnOffLED;
extern const time_t LEDOnTime = 250;

const char index_html[] PROGMEM =
    R"rawliteral(<html><body>Hello</body></html>)rawliteral";

void handleRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", index_html);
  LEDOn = true;
  digitalWrite(8, LED_ON);
  turnOffLED = millis() + LEDOnTime;
}

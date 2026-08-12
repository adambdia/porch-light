#include "WebHandlers.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <time.h>

extern volatile bool LEDOn;
extern volatile time_t turnOffLED;
extern const time_t LEDOnTime = 250;

const char index_html[] PROGMEM =
    R"rawliteral(<html><body>Hello, it is %DATETIME%</body></html>)rawliteral";

void handleRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", index_html, rootProcessor);
  LEDOn = true;
  digitalWrite(8, LED_ON);
  turnOffLED = millis() + LEDOnTime;
}

String rootProcessor(const String &var) {
  if (var == "DATETIME") {
    time_t now = time(nullptr);
    struct tm timeinfo;
    localtime_r(&now, &timeinfo);
    char time_string[64];
    strftime(time_string, sizeof(time_string), "%B %d, %Y - %H:%M:%S",
             &timeinfo);
    return String(time_string);
  }

  return String("NaN");
}

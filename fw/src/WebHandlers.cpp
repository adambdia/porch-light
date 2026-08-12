#include "WebHandlers.h"
#include "Light.h"
#include "WebPage.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

extern volatile bool LEDOn;
extern volatile time_t turnOffLED;
extern const char index_html[] PROGMEM;

AsyncWebServer server(80);

void initWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  // server.on("/light", HTTP_GET, handleToggle);
  server.on("/lightOverride", HTTP_GET, handleLightOverride);
  server.begin();
}

void handleRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", index_html);
}

void handleLightOverride(AsyncWebServerRequest *request) {
  overrideLight();
  request->send(200, "text/plain", "OK");
}

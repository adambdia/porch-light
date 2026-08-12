#include "WebHandlers.h"
#include "WebPage.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

extern volatile bool LEDOn;
extern volatile time_t turnOffLED;
extern const char index_html[] PROGMEM;

AsyncWebServer server(80);

void initWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/light", HTTP_GET, handleRoot);
  server.begin();
}

void handleRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", index_html);
}

void handleLight(AsyncWebServerRequest *request) {
  request->send(200, "text/plain", "OK");
}

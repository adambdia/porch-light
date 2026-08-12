#include <ESPAsyncWebServer.h>

#ifndef WEBHANDLERS_H
#define WEBHANDLERS_H

#define LED_ON LOW
#define LED_OFF HIGH

void handleRoot(AsyncWebServerRequest *request);
void handleLight(AsyncWebServerRequest *request);

#endif

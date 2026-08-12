#include <ESPAsyncWebServer.h>

#ifndef WEBHANDLERS_H
#define WEBHANDLERS_H

#define LED_ON LOW
#define LED_OFF HIGH

void handleRoot(AsyncWebServerRequest *request);
void handleUpdate(AsyncWebServerRequest *request);

String rootProcessor(const String &var);

#endif

#include <ESPAsyncWebServer.h>

#ifndef WEBHANDLERS_H
#define WEBHANDLERS_H

void initWebServer();
void handleRoot(AsyncWebServerRequest *request);
void handleLight(AsyncWebServerRequest *request);

#endif

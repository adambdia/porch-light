#include "WebHandlers.h"
#include "WifiManager.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  initWifi();
  initWebServer();
}

void loop() {}

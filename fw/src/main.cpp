#include "APIClient.h"
#include "Button.h"
#include "Light.h"
#include "Schedule.h"
#include "WebHandlers.h"
#include "WifiManager.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  initWifi();
  initAPIClient();
  initSchedule();
  initWebServer();
  initLight();
  initButton();
}

void loop() {
  loopWebServer();
  loopSchedule();
  loopButton();
  loopLight();
}

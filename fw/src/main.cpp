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
  initSchedule();
  initWebServer();
  initLight();
}

const time_t print_delay = 5000;
time_t last_print = 0;
void loop() {
  loopSchedule();
  loopLight();
}

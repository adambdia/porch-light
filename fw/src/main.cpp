#include "secrets.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WebHandlers.h>
#include <WiFi.h>
#include <time.h>

AsyncWebServer server(80);

const char *HOSTNAME = "Porch Light Controller";
const char *tz_info = "EST5EDT,M3.2.0,M11.1.0";

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setHostname(HOSTNAME);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  configTzTime(tz_info, "pool.ntp.org");

  printf("Waiting for time sync...\n");
  time_t now = time(nullptr);
  while (now < 1000000000) {
    delay(500);
    now = time(nullptr);
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/light", HTTP_GET, handleRoot);

  server.begin();
}

void loop() {}

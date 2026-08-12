#include "WifiManager.h"
#include "secrets.h"
#include <Arduino.h>
#include <WiFi.h>

const char *HOSTNAME = "Porch Light Controller";

void initWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setHostname(HOSTNAME);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    printf(".");
  }
}

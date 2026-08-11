#include "secrets.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WebHandlers.h>
#include <WiFi.h>

AsyncWebServer server(80);

const char *HOSTNAME = "Porch Light Controller";
const time_t LEDOnTime = 250;
volatile time_t turnOffLED = 0;
volatile bool LEDOn = false;

void setup() {
  Serial.begin(115200);
  delay(1000); // Give the serial monitor a second to initialize

  pinMode(8, OUTPUT);
  digitalWrite(8, LED_OFF);

  // 1. Start the Wi-Fi connection
  Serial.println();
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setHostname(HOSTNAME);

  // 2. Wait in a loop until it connects
  // (This prints a dot every half second while connecting)
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // 3. Connection successful!
  Serial.println("");
  Serial.println("Wi-Fi connected successfully!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);

  server.begin();
}

void loop() {
  if (LEDOn && millis() >= turnOffLED) {
    digitalWrite(8, LED_OFF);
    LEDOn = false;
  }
}

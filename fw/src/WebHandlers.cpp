#include "WebHandlers.h"
#include "Light.h"
#include "Schedule.h"
#include "WebPage.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <cstdint>
#include <time.h>

extern const char index_html[] PROGMEM;
static const bool IS_POST = true;

AsyncWebServer server(80);
void handleRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", index_html);
}

void handleLightOverride(AsyncWebServerRequest *request) {
  overrideLight();
  request->send(200, "text/plain", "OK");
}

void handleUpdateSchedule(AsyncWebServerRequest *request) {
  bool useSunrise = false;
  bool useSunset = false;
  uint32_t duration = 10 * 60 * 1000; // 10 minutes

  struct tm onTime = {};
  struct tm offTime = {};

  // pull values out of form
  if (request->hasParam("useSunrise", IS_POST))
    useSunrise = true;

  if (request->hasParam("useSunset", IS_POST))
    useSunset = true;

  if (request->hasParam("tomorrowOffHour", IS_POST)) {
    offTime.tm_hour =
        request->getParam("tomorrowOffHour", IS_POST)->value().toInt();
  }

  if (request->hasParam("tomorrowOffMinute", IS_POST)) {
    offTime.tm_min =
        request->getParam("tomorrowOffMinute", IS_POST)->value().toInt();
  }

  if (request->hasParam("tomorrowOnHour", IS_POST)) {
    onTime.tm_hour =
        request->getParam("tomorrowOnHour", IS_POST)->value().toInt();
  }

  if (request->hasParam("tomorrowOnMinute", IS_POST)) {
    onTime.tm_min =
        request->getParam("tomorrowOnMinute", IS_POST)->value().toInt();
  }

  if (request->hasParam("overrideDuration", IS_POST)) {
    duration = request->getParam("overrideDuration", IS_POST)->value().toInt();
    duration = duration * 1000; // s to ms
  }

  updateScheduleFromWeb(onTime, offTime, useSunrise, useSunset);
  setOverrideDuration(duration);
  request->send(200, "text/plain", "OK");
}

void initWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  // server.on("/light", HTTP_GET, handleToggle);
  server.on("/lightOverride", HTTP_GET, handleLightOverride);
  server.on("/updateSchedule", HTTP_POST, handleUpdateSchedule);
  server.begin();
}

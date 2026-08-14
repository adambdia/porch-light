#include "APIClient.h"
#include "secrets.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <cstdio>
#include <cstring>

static const int HTTP_OK = 200;
static const char *endpoint =
    "http://api.sunrise-sunset.org/v2?time_format=unix";
static JsonDocument filter;

void initAPIClient() {
  // only values we care about from the API call
  filter["first_light"] = true;
  filter["sunset"] = true;
}

void fetchSunTimes(time_t *sunrise, time_t *sunset) {
  if (!sunrise || !sunset) // in case nullptr was passed in
    return;
  WiFiClient client;
  HTTPClient http;
  JsonDocument doc;
  char url[128];

  // lat long kept in secrets.h
  snprintf(url, sizeof(url), "%s%s", endpoint, LAT_LONG_API_PARAM);

  http.useHTTP10(true);
  http.begin(client, url);
  int statusCode = http.GET();
  if (statusCode != HTTP_OK) // exit if GET was unsuccessful
  {
    http.end();
    return;
  }

  DeserializationError error = deserializeJson(
      doc, http.getStream(), DeserializationOption::Filter(filter));
  if (error) {
    http.end();
    return;
  }

  // use first_light as it makes more sense
  *sunrise = doc["first_light"].as<time_t>();
  *sunset = doc["sunset"].as<time_t>();
  http.end();
}

#include <Arduino.h>

#define LEDPIN 8
#define PERIOD 250

void setup() { pinMode(LEDPIN, OUTPUT); }

void loop() {
  digitalWrite(LEDPIN, HIGH);
  delay(PERIOD);
  digitalWrite(LEDPIN, LOW);
  delay(500);
}

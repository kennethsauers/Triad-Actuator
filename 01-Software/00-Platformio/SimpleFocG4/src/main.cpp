#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial to connect, needed for native USB sometimes
  Serial.println("starting");
}

void loop() {
  Serial.println("here");
  delay(1000);
}


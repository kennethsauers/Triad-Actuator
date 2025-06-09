#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);
int i = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(5000);
  Serial.println("Starting Application, end of setup");
}

void loop() {
  i++;
  Serial.println(myFunction(i,i));
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
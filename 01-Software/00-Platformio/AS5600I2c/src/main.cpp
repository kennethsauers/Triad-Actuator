#include <Arduino.h>
#include <Wire.h>
#include <AS5600.h>

//  Uncomment the line according to your sensor type
//AS5600L as5600;   //  use default Wire
AS5600 as5600;   //  use default Wire

uint32_t start, stop;
void setup() {
  // Setup i2c Wire
  Wire.setSCL(PB8);
  Wire.setSDA(PB9);
  Wire.begin();


  // Setup Serial Interface
  Serial.begin(9600);
  delay(1000);

  Wire.begin();
  Serial.println(as5600.getAddress());

  //  as5600.setAddress(0x40);  //  AS5600L only

  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);
  as5600.setSlowFilter(0);
  as5600.setFastFilter(4);
}
static uint32_t lastTime = 0;


void loop() {
  const int sampleCount = 100;
  uint16_t angleData[sampleCount];

  // Collect 100 samples
  for (int i = 0; i < sampleCount; i++) {
    angleData[i] = as5600.rawAngle();
  }

  // Print in rows of 10
  for (int i = 0; i < sampleCount; i++) {
    Serial.print(angleData[i]);
    Serial.print("\t");

    // Print newline after every 10 values
    if ((i + 1) % 10 == 0) {
      Serial.println();
    }
  }

  // Optional: "clear" the array by setting to 0
  for (int i = 0; i < sampleCount; i++) {
    angleData[i] = 0;
  }

  Serial.println("\nWaiting 5 seconds...\n");
  delay(5000);
}

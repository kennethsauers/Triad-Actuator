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
}

void loop()
{
  static uint32_t lastTime = 0;

  if (millis() - lastTime >= 100)
  {
    lastTime = millis();
    as5600.readAngle();
    Serial.print(as5600.getCumulativePosition(false));
    Serial.print("\t");
    Serial.println(as5600.getAngularSpeed(AS5600_MODE_DEGREES, false));
  }
  else{
    as5600.getCumulativePosition(false);
  }
}
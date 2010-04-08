#include <Wire.h>

#define address 0x61                  // The address of the SD21
#define servo 0x3F                    // Address of first servo

void setup(){
  Wire.begin();
}

void loop(){
  Wire.beginTransmission(address);
    Wire.send(servo);
    Wire.send(255);                   // Send a value of 255 to servo 1
  Wire.endTransmission();
  delay(1000);
  Wire.beginTransmission(address);
    Wire.send(servo);
    Wire.send(128);                   // Send a value of 128 to servo 1
  Wire.endTransmission();
  delay(1000);
  Wire.beginTransmission(address);
    Wire.send(servo);
    Wire.send(0);                     // Send a value of 0 to servo 1
  Wire.endTransmission();
  delay(1000);
  Wire.beginTransmission(address);
    Wire.send(servo);
    Wire.send(128);                   // send a value of 128 to servo 1
  Wire.endTransmission();
  delay(1000);
}

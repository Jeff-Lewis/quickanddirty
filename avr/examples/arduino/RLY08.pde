/*
Arduino example for the RLY08.
Turns relay 1 on and off again at regualr intervals.
*/

#include <Wire.h>

#define address 0x38

void setup(){
  Wire.begin();
  Serial.begin(9600);
  
  Wire.beginTransmission(address);
  Wire.send(0x00);                        // Sends command register to get software version
  Wire.endTransmission();
  Wire.requestFrom(address, 1);           // Requests one byte form RLY08
  while(Wire.available() < 1);            // Wait for it to arrive
  int soft = Wire.receive();              // Gets the byte
  Serial.println(soft, DEC);              // Prints it to the arduino serial monitor
}

void loop(){
  Wire.beginTransmission(address);
  Wire.send(0x00);                        // Sends command byte to RLY08
  Wire.send(0x65);                        // Turns on relay 1
  Wire.endTransmission();
  delay(1000);
  Wire.beginTransmission(address);
  Wire.send(0x00);                        // Sends command byte
  Wire.send(0x6F);                        // Turns off relay 1
  Wire.endTransmission();
  delay(1000);
}

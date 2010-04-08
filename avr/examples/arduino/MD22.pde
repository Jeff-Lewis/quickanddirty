/*
MD22 example code for arduino. Demonstrates acceleration.
*/


#include <SoftwareSerial.h>
#include <Wire.h>

#define rxPin 2                                       // rx pin for LCD03
#define txPin 3                                       // tx pin for LCD03
#define md22Address 0x58                              // address of md 22 (all mode switches on)
#define softReg 0x07                                  // Byte for reading software register
#define motor1 0x01                                   // Byte for first motor
#define motor2 0x02                                   // Byte for second motor
#define accelReg 0x03                                // Byte to set acelleration


SoftwareSerial lcd_03 = SoftwareSerial(rxPin, txPin); // Sets up a software serial port for LCD03

void setup(){
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  lcd_03.begin(9600);                                 // Begin serial with LCD03
  Wire.begin();
  delay(100);                                         // Wait for everything to be powered up
  
  lcd_03.print(0x0C, BYTE);                           // Clear the LCD03 screen
  getSoftware();                                      // Function that gets and prints software revision to screen
  setMode();                                          // Function that sets mode to 2 and sets acceleration
}

void loop(){
  delay(1390);
  
  Wire.beginTransmission(md22Address);                // Set first motor to a speed of 255
  Wire.send(motor1);
  Wire.send(255);
  Wire.endTransmission();
  
  Wire.beginTransmission(md22Address);                // Set second motor to stop
  Wire.send(motor2);
  Wire.send(128);
  Wire.endTransmission();
  
  delay(1390);
  
  Wire.beginTransmission(md22Address);                // Set first motor to speed 0
  Wire.send(motor1);
  Wire.send(0);
  Wire.endTransmission();
  
  Wire.beginTransmission(md22Address);                // Set second motor to stop
  Wire.send(motor2);
  Wire.send(128);
  Wire.endTransmission();
  
  delay(1390);
  
  Wire.beginTransmission(md22Address);                // Set first motor to stop
  Wire.send(motor1);
  Wire.send(128);
  Wire.endTransmission();
  
  Wire.beginTransmission(md22Address);                // Set second motor to speed 255
  Wire.send(motor2);  
  Wire.send(255);
  Wire.endTransmission();
  
  delay(1390);
  
  Wire.beginTransmission(md22Address);                // set first motor to stop
  Wire.send(motor1);
  Wire.send(128);
  Wire.endTransmission();
  
  Wire.beginTransmission(md22Address);                // Set second motor to speed 0
  Wire.send(motor2);
  Wire.send(0);
  Wire.endTransmission();
}

void getSoftware(){                                   // Reads abd displays the software version of MD22
  Wire.beginTransmission(md22Address);                // Calles software register
  Wire.send(softReg);
  Wire.endTransmission();
  
  Wire.requestFrom(md22Address, 1);                   // Requests one byte
  while(Wire.available() < 1);                        // Wait for it to arrive
  int software = Wire.receive();                      // Get byte
  lcd_03.print("MD22 Example   V:");
  lcd_03.print(software, DEC);                        // Print byte to LCD03
}

void setMode(){
  Wire.beginTransmission(md22Address);                // Set a value of 255 to the acceleration register
  Wire.send(accelReg);
  Wire.send(0xFF);
  Wire.endTransmission();
}

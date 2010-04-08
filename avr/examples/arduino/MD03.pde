/*
MD03 example for arduino
*/

#include <Wire.h>
#include <SoftwareSerial.h>

#define address 0x58                    // Address of MD03
#define softReg 0x07                    // Byte to read software
#define cmdByte 0x00                    // Command byte
#define speedByte 0x02                  // Byte to write to speed register
#define tempReg 0x04                    // Byte to read temprature
#define currentReg 0x05                 // Byte to read motor current
#define rxPin 2                         // Sets rx pin
#define txPin 3                         // Sets tx pin

SoftwareSerial lcd_03 = SoftwareSerial(rxPin, txPin);  // Sets up serial for LCD03

int direct = 1;                         // Stores what direction the motor should run in

void setup(){
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  lcd_03.begin(9600);                   // Begin serial for LCD03
  
  Wire.begin();
  delay(100);
  
  lcd_03.print(0x04, BYTE);             // Hides LCD03 cursor
  lcd_03.print(0x0C, BYTE);             // Clears LCD03 screen
  
  int software = getData(softReg);      // Gets software version and prints it to LCD03
  lcd_03.print("MD03 Example  V:");
  lcd_03.print(software);
}

void loop(){
  for(int i = 0; i < 250; i=i+10){
    sendData(speedByte, i);             // Sets speed to i
    sendData(cmdByte, direct);          // Sets motor to direct, a value of 1 runs the motor forward and 2 runs backward
    int temp = getData(tempReg);        // Gets temperature
    lcd_03.print(0x02, BYTE);
    lcd_03.print(21, BYTE);
    lcd_03.print("temprature: ");
    lcd_03.print(temp);                 // Prints temperature to LCD03
    lcd_03.print("  ");                 // Prints spaces to clear space after data
    delay(50);                          // Wait to make sure all data sent
    int current = getData(currentReg);  // Gets motor current
    lcd_03.print(0x02, BYTE);
    lcd_03.print(41, BYTE);
    lcd_03.print("Motor current: ");
    lcd_03.print(current);              // Prints current to LCD03
    lcd_03.print("   ");                // Prints spaces to clear space after data
    delay(50);                          // Wait to make sure all data sent  
  }
  if(direct == 1)                       // If loop that swaps value of direct between 1 and 2 each time through loop
    direct = 2;                        
  else
    direct = 1;                        
}

int getData(int reg){                   // function for getting data from MD03
Wire.beginTransmission(address);
  Wire.send(reg);                       // Send reg to mdo3
  Wire.endTransmission();
  
  Wire.requestFrom(address, 1);         // Requests byte from MD03
  while(Wire.available() < 1);          // Waits for byte
  int data = Wire.receive();            // Gets it

  return(data);                         // Returns byte
}

void sendData(int reg, int val){        // Function for sending data to MD03
  Wire.beginTransmission(address);      
  Wire.send(reg);                       // Send register to write to
  Wire.send(val);                       // send value to be sent to it
  Wire.endTransmission();
}

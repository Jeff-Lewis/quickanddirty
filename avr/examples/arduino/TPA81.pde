#include <Wire.h>
#include <SoftwareSerial.h>

#define rxPin 2                                        // Pin for rx
#define txPin 3                                        // Pin for tx
#define address 0x68                                   // Address of TPA81
#define softReg 0x00                                   // Byte for software version
#define ambiant 0x01                                   // Byte for ambiant temperature
#define hideCsr 0x04                                   // Byte to hide LCD03 cursor
#define clrScrn 0x0C                                   // Byte to move LCD03 cursor
#define crgRtn 0x0D                                    // Byte to perform a carriage return on LCD03
#define csrMv 0x02                                     // Byte to move sursor

SoftwareSerial lcd_03 = SoftwareSerial(rxPin, txPin);  // Defines serial port for LCD03

int temperature[] = {0,0,0,0,0,0,0,0};                 // Array to hold temperature data

void setup(){
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  lcd_03.begin(9600);                                  // Starts software serial port for LCD03
  Wire.begin();
  delay(100);                                          // Wait to make sure everything is powerd up
  
  lcd_03.print(clrScrn, BYTE);    
  lcd_03.print(hideCsr, BYTE);
  int software = getData(softReg);                     // Get software version 
  lcd_03.print("TPA81 Example  V:");
  lcd_03.print(software);                              // Print software version to the screen
}
  
void loop(){
  for(int i = 0; i < 8; i++){                          // Loops and stores temperature data in array
  temperature[i] = getData(i+2);
  }
  
  lcd_03.print(csrMv, BYTE);                            
  lcd_03.print(21, BYTE);                              // Moves cursor to space 21

  for(int x = 0; x < 8; x++){                          // Loop prints each member of temperature to LCD03 followed by a space
    if(x==4)                                           // If x is 4 perform a carriage return to format the results on the LCD03 for easier reading
      lcd_03.print(crgRtn, BYTE); 
    lcd_03.print(temperature[x]);
    lcd_03.print(" ");
    delay(50);                                         // Wait befor printing next value to give time for everything to be sent
  }
  
  lcd_03.print(crgRtn, BYTE);                          
  int ambiantTemp = getData(ambiant);                  // Get reading of ambiant temperature and print to LCD03 screen
  lcd_03.print("Ambiant: ");
  lcd_03.print(ambiantTemp);
}

int getData(int reg){                                  // Function to receive one byte of data from TPA81
  Wire.beginTransmission(address);                     // Begin communication with TPA81
  Wire.send(reg);                                      // Send reg to TPA81
  Wire.endTransmission();
  Wire.requestFrom(address, 1);                        // Request 1 byte
  while(Wire.available() < 1);                         // Wait for byte to arrive
  int data = Wire.receive();                           // Get byte
  return(data);                                        // return byte
}

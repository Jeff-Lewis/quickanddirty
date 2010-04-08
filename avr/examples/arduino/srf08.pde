/*
Generic example for the SRF modules 02, 08, 10 and 235.
Only the SRF08 uses the light saensor so when any other 
range finder is used with this code the light reading will 
be a constant value. 
*/

#include <Wire.h>
#include <SoftwareSerial.h>

#define rxPin 2                                   // Software serial pin for rx
#define txPin 3                                   // Software serial pin for tx
#define srfAddress 0x70                           // Address of the SRF08
#define cmdByte 0x00                              // Command byte
#define lightByte 0x01                            // Byte to read light sensor
#define rangeByte 0x02                            // Byte for start of ranging data
#define clrScrn 0x0C                              // Byte to clear LCD03 screen
#define mvCsr 0x02                                // Byte to tell LCD03 we wish to move cursor
#define hideCsr 0x04                              // Byte to hide the cursor

SoftwareSerial lcd_03 =  SoftwareSerial(rxPin, txPin);    // defines a new software serial port for lcd_03

byte highByte = 0x00;                             // Stores high byte from ranging
byte lowByte = 0x00;                              // Stored low byte from ranging

void setup(){
  
  lcd_03.begin(9600);                             // Begins serial port for LCD_03
  Wire.begin();                               
  delay(100);                                     // Waits to make sure everything is powered up before sending or receiving data
  
  pinMode(rxPin, INPUT);                                   
  pinMode(txPin, OUTPUT);
  lcd_03.print(clrScrn, BYTE);
  lcd_03.print(hideCsr, BYTE);
  lcd_03.println("SRF02/08/10/235");
  
  int softRev = getSoft();                        // Calls function to get software revision
  lcd_03.print(mvCsr, BYTE);
  lcd_03.print(0x3D, BYTE);                       // Move cursor to space 16
  lcd_03.print("Software version: ");
  lcd_03.print(softRev, DEC);                     // Print softRev to LCD03
    
}

void loop(){
  
  int rangeData = getRange();                     // Calls a function to get range
  lcd_03.print(mvCsr, BYTE);
  lcd_03.print(0x15, BYTE);                       // Move cursor to space 21
  lcd_03.print("Range = ");
  lcd_03.print(rangeData, DEC);                   // Print rangeData to LCD03
  lcd_03.print("   ");                            // Print some spaces to slear spaces after data
 
  int lightData = getLight();                     // Call function to get light reading and store in lightData
  lcd_03.print(mvCsr, BYTE);
  lcd_03.print(41, BYTE);                         // Move cursor to space 41
  lcd_03.print("light = ");
  lcd_03.print(lightData, DEC);                   // Display lightData
  lcd_03.print("  ");                             // Print some spaces to slear spaces after data 
  
 delay(100);                                      // Wait before looping
}

int getRange(){                                   // This function gets a ranging from the SRF08
  
  int range = 0; 
  
  Wire.beginTransmission(srfAddress);             // Start communticating with SRF08
  Wire.send(cmdByte);                             // Send Command Byte
  Wire.send(0x51);                                // Send 0x51 to start a ranging
  Wire.endTransmission();
  
  delay(100);                                     // Wait for ranging to be complete
  
  Wire.beginTransmission(srfAddress);             // start communicating with SRFmodule
  Wire.send(rangeByte);                           // Call the register for start of ranging data
  Wire.endTransmission();
  
  Wire.requestFrom(srfAddress, 2);                // Request 2 bytes from SRF module
  while(Wire.available() < 2);                    // Wait for data to arrive
  highByte = Wire.receive();                      // Get high byte
  lowByte = Wire.receive();                       // Get low byte

  range = (highByte << 8) + lowByte;              // Put them together
  
  return(range);                                  // Returns Range
}

int getLight(){                                   // Function to get light reading
  
  Wire.beginTransmission(srfAddress);
  Wire.send(lightByte);                           // Call register to get light reading
  Wire.endTransmission();
  
  Wire.requestFrom(srfAddress, 1);                // Request 1 byte
  while(Wire.available() < 0);                    // While byte available
  int lightRead = Wire.receive();                 // Get light reading
    
  return(lightRead);                              // Returns lightRead
  
}

int getSoft(){                                    // Function to get software revision
  
  Wire.beginTransmission(srfAddress);             // Begin communication with the SRF module
  Wire.send(cmdByte);                             // Sends the command bit, when this bit is read it returns the software revision
  Wire.endTransmission();
  
  Wire.requestFrom(srfAddress, 1);                // Request 1 byte
  while(Wire.available() < 0);                    // While byte available
  int software = Wire.receive();                  // Get byte
    
  return(software);                               
  
}

/*******************************************************
*           SRF08 and LCD03 arduino example            *
*             Using wire & LCDi2c librarys             *
* By default the LCDi2c library turns the backlight on *
*                                                      *
*                By James Henderson 2009               *
*******************************************************/

#include <Wire.h>
#include <LCDi2cR.h>

LCDi2cR lcd = LCDi2cR(4,40,0x63,0);                  // Creates variable called lcd used for communication with LCD03

#define srf08 0x70                                   // The address of the SRF08
#define srf_cmd 0x00                                 // SRF08 command byte (when read returns software version)
#define range_cmd 0x51                               // Command to start the SRF08 ranging
#define range_byte 0x02                              // Read from here to get the high and low byte of ranging
#define light_byte 0x01                              // Read from here to get the light value from the SRF08

int highByte, lowByte, range, light, software = 0;   // Variables for the high and low byte of ranging, the actual ranging, light value and software revision
                 
void setup(){
  Wire.begin();
  lcd.init();                                        // Initialises the LCD screen clearing the screen and setting cursor to home
  Wire.beginTransmission(srf08);                     // Reading the software version of the SRF08
    Wire.send(srf_cmd);
  Wire.endTransmission();
  Wire.requestFrom(srf08, 1);                        // Request byte for software revision     
  while(Wire.available() < 1);                       // Wait fdor it to arrive
  software = Wire.receive();                         // Get software revision
  setupDisplay(software);                            // Function to format the layout of data on the screen
}

void loop(){
  Wire.beginTransmission(srf08);
    Wire.send(srf_cmd);
    Wire.send(range_cmd);                            // Send the byte to start a ranging to the command register
  Wire.endTransmission();
  delay(100);                                        // Wait some time for ranging to complete
  Wire.beginTransmission(srf08);
    Wire.send(range_byte);                           // Send byte where ranging data is stored
  Wire.endTransmission();
  Wire.requestFrom(srf08, 2);                        // request 2 bytes from SRF08
  while(Wire.available() < 2);                       // Wait for them to arrive
  highByte = Wire.receive();                         // Get the high byte of ranging
  lowByte = Wire.receive();                          // Get the low byte of ranging
  range = (highByte << 8) + lowByte;                 // Put them together
  Wire.beginTransmission(srf08);
    Wire.send(light_byte);                           // Send byte where light reading is stored
  Wire.endTransmission();
  Wire.requestFrom(srf08, 1);                        // Request a byte
  while(Wire.available() < 1);                       // Wait for it
  light = Wire.receive();                            // Get it
  displayData(range, light);                        // Calls a function to display range and light values in the appropriate places on the lcd screen
}

void setupDisplay(int softwareRev){
  lcd.home();                                       // Cursor to home position (0,0)
  lcd.println("LCD03 & SRF08 demo");                // Some tect to screen
  lcd.setCursor(1,0);                               // Move cursor to row 1 column 0
  lcd.print("Range: ");
  lcd.setCursor(2,0);
  lcd.print("light: ");
  lcd.setCursor(3,0);
  lcd.print("Software v: ");
  lcd.print(softwareRev);                           // Display software revision
}

void displayData(int rangeData, int lightData){
  lcd.setCursor(1,8);                              // Move cursor
  lcd.print(rangeData);                            // Display range followed by some blank space
  lcd.print("   ");
  lcd.setCursor(2,8);                              // Move cursor
  lcd.print(lightData);                            // Display light data followed by some blank space
  lcd.print("   ");
}

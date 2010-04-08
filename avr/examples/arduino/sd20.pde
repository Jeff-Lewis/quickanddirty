/*
Example for SD20 servo driver chip. This will drive a servo from the
first servo pin on the SD20 from 1ms to 2ms repeatedly. This also shows
how to how to set use the expand mode to set custom ranges.
*/

#include <Wire.h>

#define sd20Address 0x61                // Address of the SD20
#define getSoft 0x00                    // Byte to get software version
#define servPin 0x01                    // Byte address for first servo pin


int softVer = 0;                        // Stores software version 

void setup(){
  Wire.begin();                          
  Serial.begin(9600);
  Software();                           // Call function that reads software version
  setExpand();                          // Calls function that sets expand mode values for servo movement
}

void loop(){
  
  Wire.beginTransmission(sd20Address);  // Send value of 254 to first servo pin
  Wire.send(servPin);
  Wire.send(254);
  Wire.endTransmission();
  delay(1000);
  
  Wire.beginTransmission(sd20Address);  // Send value of 1 to first servo pin
  Wire.send(servPin);
  Wire.send(1);
  Wire.endTransmission();
  delay(1000);    
      
}

void setExpand(){                       // Function to define custom settings for expanded mode 
  
  Wire.beginTransmission(sd20Address);  // Send 64 to register 21
  Wire.send(0x15);
  Wire.send(0x40);
  Wire.endTransmission();
  
  delayMicroseconds(70);                // Wait for SD20 to process the byte we just sent to it
  
  Wire.beginTransmission(sd20Address);  // Send 3 to register 22
  Wire.send(0x16);
  Wire.send(0x03);
  Wire.endTransmission();
  
  delayMicroseconds(70);                // Wait for SD20 to process the byte we just sent to it
  
  Wire.beginTransmission(sd20Address);  // send 212 to register 23
  Wire.send(0x17);
  Wire.send(0xD4);
  Wire.endTransmission();
}

void Software(){                        // Function that reads software revision
  Wire.beginTransmission(sd20Address);  
  Wire.send(getSoft);                   // Send to the register that returns the software revision
  Wire.endTransmission();               
  
  Wire.requestFrom(sd20Address, 1);     // Request 1 byte from SD20
  while(Wire.available() > 0){          // While there are bytes to read
  softVer = Wire.receive();             // Get software revision
  }
  Serial.println(softVer);              // Print software version to arduino serial monitor
}

/*
Arduino example for SRF05
Using a single pin for both trigger and echo.
*/

int duration;                          // Stores duratiuon of pulse in
int distance;                          // Stores distance
int srfPin = 2;                        // Pin for SRF05

void setup(){
Serial.begin(9600);
}

void loop(){
  pinMode(srfPin, OUTPUT);
  digitalWrite(srfPin, LOW);           // Make sure pin is low before sending a short high to trigger ranging
  delayMicroseconds(2);
  digitalWrite(srfPin, HIGH);          // Send a short 10 microsecond high burst on pin to start ranging
  delayMicroseconds(10);
  digitalWrite(srfPin, LOW);           // Send pin low again before waiting for pulse back in
  pinMode(srfPin, INPUT);
  duration = pulseIn(srfPin, HIGH);    // Reads echo pulse in from SRF05 in micro seconds
  distance = duration/58;              // Dividing this by 58 gives us a distance in cm
  Serial.println(distance);
  delay(50);                           // Wait before looping to do it again
}

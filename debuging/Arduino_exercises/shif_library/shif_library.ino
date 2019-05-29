/*
  ShiftRegister74HC595.h - Library for easy control of the 74HC595 shift register.
  Created by Timo Denk (www.simsso.de), Nov 2014.
  Additional information are available on http://shiftregister.simsso.de/
  Released into the public domain.
*/

#include <ShiftRegister74HC595.h>
// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (1, D7,D5,D6); 
void setup() {
  Serial.begin(9600);
}

void loop() {
//  sr.setAllHigh(); // set all pins HIGH
//  delay(500);
//  sr.setAllLow(); // set all pins LOW
//  delay(500); 
//  for (int i = 0; i < 8; i++) {
//    sr.set(i, HIGH); // set single pin HIGH
//    delay(2000); 
//  }
//  delay(1000);
//  for (int i = 0; i < 8; i++) {
//    sr.set(i, LOW); // set single pin HIGH
//    delay(2000); 
//  }

  sr.setAllLow();
  delay(500);
//  for (int i = 0; i < 8; i++) {
//    sr.set(i, HIGH); // set single pin HIGH
//    delay(200);
//  
//  }
//  for (int i = 8; i > 0; i--) {
//    sr.set(i, LOW); // set single pin HIGH
//    delay(200);
//  }
  // set all pins at once
  uint8_t pinValues[3][8] = {
    {B11110000},
    {B11111111},
    {B10101010}
  }; 

  for (int i = 0; i < 3; i++) {
     
     sr.setAll(pinValues[i]); 
     delay(500);
  }

  
  // read pin (zero based)
  uint8_t stateOfPin5 = sr.get(5);
  Serial.println(stateOfPin5);
}

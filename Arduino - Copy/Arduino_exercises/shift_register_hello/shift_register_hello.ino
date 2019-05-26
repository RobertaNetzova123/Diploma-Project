/*
  ShiftRegister74HC595.h - Library for easy control of the 74HC595 shift register.
  Created by Timo Denk (www.simsso.de), Nov 2014.
  Additional information are available on http://shiftregister.simsso.de/
  Released into the public domain.
*/

#define data  D7
#define clock  D5
#define latch  D6

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
//ShiftRegister74HC595 sr (1, D7,D5,D6); 
void setup() {
  Serial.begin(9600);
  pinMode(latch, OUTPUT);
  digitalWrite(latch, LOW);
  pinMode(clock, OUTPUT);
  digitalWrite(clock, LOW);
  pinMode(data, OUTPUT);
  digitalWrite(data, LOW);
}

void loop() {
digitalWrite(data,HIGH);
  for (int i = 0; i< 7; i++) {
    doLatch();
    doClock();
    }
  delay(1000);

  digitalWrite(data,LOW);
  for (int i = 0; i< 7; i++) {
    doLatch();
    }
    doClock();
    delay(1000);

//doClock();
}

void doLatch () {
  digitalWrite(latch,HIGH);
  digitalWrite(latch,LOW);
}

void doClock() {
 digitalWrite(clock,HIGH);
 digitalWrite(clock,LOW); 
}

#include "shift_165.h"
#include <Arduino.h>
unsigned long startMillis;
unsigned long currentMillis;

Shift_165::Shift_165(int enablePin, int loadPin, int clockPin, int dataPin){

  enable = enablePin;
  load = loadPin;
  clock = clockPin;
  data = dataPin;

  pinMode(load,FUNCTION_3);
  pinMode(load,OUTPUT);
  pinMode(enable,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,INPUT);
  digitalWrite(load,HIGH);
}

int* Shift_165::Shift_bytes() {
 
  digitalWrite(load,LOW);
  delay(10);
  digitalWrite(load,HIGH);
  delay(10);
  
  digitalWrite(clock,HIGH);
  digitalWrite(enable,LOW);
  byte incoming=shiftIn(data,clock,MSBFIRST);
  digitalWrite(enable,HIGH);
 
  static int pinValue[8];
  for(int i=7;i>=0;i--){
    
    if(bitRead(incoming,i)==1)
    {
      pinValue[i] = 1;
    }
    else
    {
      pinValue[i] = 0;
    }
  }
  
  return pinValue; 
}

//bool Shift_165::ShiftChecker (int duration, int checker) {
//  startMillis = millis();
//  currentMillis = millis();
//  while (currentMillis - startMillis < duration) {
//    int* shifted = Shift_bytes();
//    if (shifted[checker] == 0) {
//      return true;
//    }
//    currentMillis = millis();
//    }
//  
//  return false;
//  }

void Shift_165::ShiftPrint(int* shifted) {
//  int* s = Shift_bytes();
      for (int i = 0; i < 8; i ++) {
      Serial.print(shifted[i]);
      }
      Serial.println();
  }




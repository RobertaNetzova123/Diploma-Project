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

void Shift_165::Shift_bytes(int* arr) {

//  for (int i =0; i < 16; i++) {
//    arr[i] = 1;
//    }
 
  digitalWrite(load,LOW);
  delay(10);
  digitalWrite(load,HIGH);
  delay(10);
  
  digitalWrite(clock,HIGH);
  digitalWrite(enable,LOW);
  byte incoming[2];
  for (int i = 0; i < 2; i ++) {
    incoming[i] = shiftIn(data,clock,MSBFIRST);
    }
  
  digitalWrite(enable,HIGH);
  int q = 15;
  for (int i  = 1; i >= 0; i--) {

    for (int k = 7; k >= 0; k--,q--) { 
      if(bitRead(incoming[i],k)==1)
      {
        arr[q] = 1;
      }
      else
      {
        arr[q] = 0;
      }
      }
    }
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






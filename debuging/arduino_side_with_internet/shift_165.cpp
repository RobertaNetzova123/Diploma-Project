#include "shift_165.h"
#include <Arduino.h>
unsigned long startMillis;
unsigned long currentMillis;

Shift_165::Shift_165(int enablePin, int loadPin, int clockPin, int dataPin, int register_number){

  enable = enablePin;
  load = loadPin;
  clock = clockPin;
  data = dataPin;
  number_of_bits = register_number*8;

  pinMode(load,FUNCTION_3);
  pinMode(load,OUTPUT);
  pinMode(enable,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,INPUT);
  digitalWrite(load,HIGH);
}

void Shift_165::Shift_bytes(int* arr) {
 
  digitalWrite(load,LOW);
  delay(10);
  digitalWrite(load,HIGH);
  delay(10);
  
  digitalWrite(clock,HIGH);
  digitalWrite(enable,LOW);
  
  byte incoming[number_of_bits];
  
  for (int i = 0; i < number_of_bits; i ++) {
    incoming[i] = shiftIn(data,clock,MSBFIRST);
    }
  
  digitalWrite(enable,HIGH);
  int q = number_of_bits - 1;
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


int Shift_165::get_register_size() {
    
    return number_of_bits;
    }

void Shift_165::ShiftPrint(int* shifted) {
//  int* s = Shift_bytes();
      for (int i = 0; i < get_register_size(); i ++) {
      Serial.print(shifted[i]);
      }
      Serial.println();
  }



bool Shift_165::ShiftChecker (int duration, int checker) {
    startMillis = millis();
    currentMillis = millis();
    while (currentMillis - startMillis < duration) {
    int shifted[number_of_bits];
    Shift_bytes(shifted);
    Serial.print(shifted[checker]);
    
      if (shifted[checker] == 0) {
        Serial.println();
        return true;
      }
      currentMillis = millis();
      }
    Serial.println();
    return false;
  }






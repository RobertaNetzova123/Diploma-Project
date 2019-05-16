#include "shift_165.h"
#define enable D1
#define load 1 //d3
#define clock D8
#define data D0

Shift_165 shift = Shift_165(enable,load,clock,data);
void setup(){

//  digitalWrite(enable,HIGH);
  Serial.begin(9600);

}
 
void loop(){

   int* shifted = shift.Shift_bytes();

    while (1) {
       int* shifted = shift.Shift_bytes();
      for (int i = 0; i < 8; i ++) {
      Serial.print(shifted[i]);
      }
      Serial.println();
      yield();
//      delay(5000);
//      shifted = shift.Shift_bytes();
      
    }

    delay (8000);

}


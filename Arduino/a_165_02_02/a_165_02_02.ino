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
 Serial.print("hello1 ");   
   int shifted[16];
   shift.Shift_bytes(shifted);
    Serial.print("hello2 ");  
   
      for (int i = 0; i < 16; i ++) {
      Serial.print(shifted[i]);
      }
      Serial.println();

      delay(50);

}


#include "shift_165.h"
#define enable D1
#define load 1 //d3
#define clock D8
#define data D0
#define register_number 2
#define d D3
Shift_165 shift = Shift_165(enable,load,clock,data,register_number);
void setup(){

//  digitalWrite(enable,HIGH);
  Serial.begin(9600);
  pinMode(d, OUTPUT);
  digitalWrite(d,LOW);

}
 
void loop(){
 Serial.print("hello1 ");   
 int size = shift.get_register_size();
   int shifted[size];
   shift.Shift_bytes(shifted);
    Serial.print("hello2 ");  
   
      for (int i = 0; i < size; i ++) {
      Serial.print(shifted[i]);
      }
      Serial.println();

      delay(50);

}


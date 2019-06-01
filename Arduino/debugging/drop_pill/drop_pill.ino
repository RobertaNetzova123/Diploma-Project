
#include "motorDriver.h"
#include "pressureSensor.h"
#include "shift_165.h"

#define enable D1
#define load   1 //GPIO3
#define clock  D8
#define data   D0

#define register_number 2

Shift_165 shift_register = Shift_165(enable, load, clock, data,register_number);

int size = shift_register.get_register_size();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  int shifted[size];
  shift_register.Shift_bytes(shifted);
}

void loop() {

  if (shift_register.ShiftChecker(5000,8)) {
    Serial.println ("SUCCESS");
    }

    else Serial.println ("FAIL");

    delay (2000);
}

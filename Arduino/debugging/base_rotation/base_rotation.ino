
#include "motorDriver.h"

#define IN1   D6 
#define IN2   D7
#define PWMA  D4 //base
#define pump  D3 //PUMP
#define PWMA1 D2 // pump
#define PWMA2 D5
#define pump D3
Motor base = Motor(IN1,IN2, PWMA);

void setup() {
  pinMode(pump, OUTPUT);
  digitalWrite(pump,LOW);

  for (int i = 0; i < 3; i ++) {

      base.drive(800,200);
    base.drive(-800,200);
    }
     base.drive(-600,1000);


}

void loop() {
  // put your main code here, to run repeatedly:

}

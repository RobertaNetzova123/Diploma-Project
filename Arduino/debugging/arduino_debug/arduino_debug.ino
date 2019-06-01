
#include "motorDriver.h"
#include "pressureSensor.h"
#include "shift_165.h"

const int pin  = A0;
#define IN1   D6 
#define IN2   D7
#define PWMA  D4 //base
#define pump  D3 //PUMP
#define PWMA1 D2 // pump
#define PWMA2 D5

#define enable D1
#define load   1 //GPIO3
#define clock  D8
#define data   D0

#define register_number 2
const int neededContainer = 5;
//int* shifted;



//Motor h = Motor(IN1,IN2, PWMA);
//Motor v = Motor(IN1, IN2, PWMB);

Motor base = Motor(IN1,IN2, PWMA);
//Motor pump = Motor(IN1, IN2, PWMB);
Motor h = Motor(IN1,IN2, PWMA1);
Motor v = Motor(IN1,IN2, PWMA2);
Shift_165 shift_register = Shift_165(enable, load, clock, data,register_number);
Sensor sensor = Sensor(A0);

int size = shift_register.get_register_size();
//int *shifted;

void setup() {
  Serial.begin(9600);
  
  pinMode(pump, OUTPUT);
  digitalWrite(pump,LOW);
  
  delay(500);
   sensor.SetState();
    int shifted[size];
   shift_register.Shift_bytes(shifted);


}

void loop() {
  for (int i = 2; i < 4; i++) {
  sensor.SetState();
  delay(1000);
//  pickPill();
  while (!sensor.PressureCheck()) {
    pickPill(i);
    yield();
    }

   digitalWrite(pump,LOW);
   delay(2000);
  }
 
}
/*
 *................functions.................. 
 */
void pickPill (int cont) {
  
  movePen(1024,0,h);

  base.drive(600,1000);
  
  movePen(-1024,cont,h);
 
  
  digitalWrite(pump,HIGH);
  delay(500);
  
  movePenDown(-600,v);
  delay(1000);
  
  movePen(600,7,v);
  
  movePen(1024,0,h);
 
}


  
void movePen(int speed, int container, Motor motor) {
  
  int shifted[size];
  shift_register.Shift_bytes(shifted);
  
//  shifted = shift_register.Shift_bytes();
  
  Serial.println(shifted[container]);
  shift_register.ShiftPrint(shifted);
  
  motor.drive(speed);
  while (shifted[container] != 1) {
    shift_register.Shift_bytes(shifted);
//    shifted = shift_register.Shift_bytes();
    Serial.print(shifted[container]);
//        shift_register.ShiftPrint(shifted);       
    yield();  
    }

//  container_is_found(container,shifted);
  
  motor.brake();
  Serial.println();
  shift_register.ShiftPrint(shifted);
  Serial.println("#######");
  
  Serial.println("stop");
  delay(1000);
  }
  
// void container_is_found(int container, int* shifted) {
//  Serial.println(shifted[container]);
//  shift_register.ShiftPrint(shifted);
//
//  while (shifted[container] != 1) {
//    shift_register.Shift_bytes(shifted);
////    shifted = shift_register.Shift_bytes();
//    Serial.print(shifted[container]);
////        shift_register.ShiftPrint(shifted);       
//    yield();  
//    }
//  }


void movePenDown(int speed, Motor motor) {
  
  int shifted[size];
  shift_register.Shift_bytes(shifted);
  shift_register.ShiftPrint(shifted);
  
  Serial.println("Start motor");
  motor.drive(speed);
 
  while (!sensor.PressureCheck()) {
     shift_register.Shift_bytes(shifted);
    Serial.print(shifted[9]);
     if (shifted[9] == 1) break;
     yield();
    }
//    digitalWrite(pump,LOW);
    motor.brake();
    
//    pump.brake( );
  }


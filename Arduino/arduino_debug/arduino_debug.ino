
#include "motorDriver.h"
#include "pressureSensor.h"
#include "shift_165.h"

const int pin  = A0;
#define IN1   D6 
#define IN2   D7
#define PWMA  D4 //base
#define PWMB  D3 //pen
#define PWMA1 D2 // pump
#define PWMA2 D5

#define enable D1
#define load   1 //GPIO3
#define clock  D8
#define data   D0

const int neededContainer = 7;


Motor base = Motor(IN1,IN2, PWMA);
Motor pump = Motor(IN1, IN2, PWMB);
Motor h = Motor(IN1,IN2, PWMA1);
Motor v = Motor(IN1,IN2, PWMA2);
Shift_165 shift_register = Shift_165(enable, load, clock, data);
Sensor sensor = Sensor(A0);
void setup() {
  Serial.begin(9600);
  // Filling the register with states from the optrones;
  shift_register.Shift_bytes();
 
}

void loop() {
  sensor.SetState();
  pickPill();
//  while (!PressureCheck()) {
//    pickPill();
//    yield();
//    }
    

//OFFFFFF
//  Serial.println("PUMP OFF");
////  delay(2000);
//  pump.brake();
//  delay(2000);
//  Serial.println("##########");
//  delay (2000);

 
}
/*
 *................functions.................. 
 */
void pickPill () {
//  Serial.println("BASE");
//  delay(2000);
//  base.drive(800,2000);
//  delay(2000);
//  
//  Serial.println("Horizontal R");
//  delay(2000);
//  movePen(1024,neededContainer,h);
//  delay(2000);
//
  Serial.println("PUMP");
  pump.drive(1000);
//  delay(1000);
  
  Serial.println("DOWN");
//  delay(1000);
  movePenDown(1024,v);
   delay(1000);

delay(3000);
//  Serial.println("UP");
//  delay(2000);
//  movePen(-1024,neededContainer,v);
//  delay(2000);
//  
//  Serial.println("Horizontal L");
//  delay(2000);
//  movePen(-1024,neededContainer,h);
//  delay(2000);
  }

  
void movePen(int speed, int container, Motor motor) {
  int* shifted = shift_register.Shift_bytes();
  Serial.println(shifted[container]);
  motor.drive(speed);
  while (shifted[container] != 0) {
    shifted = shift_register.Shift_bytes();
    Serial.print(shifted[container]);
//        shift_register.ShiftPrint(shifted);       
    yield();  
    }
  motor.brake();
  
  Serial.println("stop");
  }
 
void movePenDown(int speed, Motor motor) {
  Serial.println("Start motor");
  motor.drive(speed);
  while (!sensor.PressureCheck()) {
    yield();
    }
    motor.brake();
    pump.brake();
  }


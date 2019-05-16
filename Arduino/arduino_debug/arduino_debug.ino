
#include "motorDriver.h"
#include "pressureSensor.h"
#include "shift_165.h"

const int pin  = A0;
#define IN1   D6 
#define IN2   D7
#define PWMA  D4 //base
#define PWMB  D3 //PUMP
#define PWMA1 D2 // pump
#define PWMA2 D5

#define enable D1
#define load   1 //GPIO3
#define clock  D8
#define data   D0

const int neededContainer = 5;
int* shifted;

//Motor h = Motor(IN1,IN2, PWMA);
//Motor v = Motor(IN1, IN2, PWMB);

Motor base = Motor(IN1,IN2, PWMA);
//Motor pump = Motor(IN1, IN2, PWMB);
Motor h = Motor(IN1,IN2, PWMA1);
Motor v = Motor(IN1,IN2, PWMA2);
Shift_165 shift_register = Shift_165(enable, load, clock, data);
Sensor sensor = Sensor(A0);
void setup() {
  Serial.begin(9600);
  // Filling the register with states from the optrones;
  int* shifted = shift_register.Shift_bytes();
  pinMode(PWMB, OUTPUT);
  digitalWrite(PWMB,LOW);
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

//  Serial.println("pump");
//  pump.drive(1024);


//  
  Serial.println("horizontal");
  movePen(1024,0,h);
  Serial.println("base");
  base.drive(600,1000);
  delay(1000);
  Serial.println("horizontal");
  movePen(-1024,6,h);
  delay (1000);

  Serial.println("pump");
//  pump.drive(1024);
  digitalWrite(PWMB,HIGH);
  delay(500);
  
  Serial.println("vertical");
  v.drive(-600,1000);
  movePen(600,7,v);

  Serial.println("horizontal");
  movePen(1024,0,h);
 
//  pump.brake();
  digitalWrite(PWMB,LOW);
  delay(3000);


//
//
//  Serial.println("pump BRAKE");
//  h.drive(1024,1000);
//  Serial.println("Container 4");
//  


//  base.drive(600,1000);
//  delay(1000);

}


  
void movePen(int speed, int container, Motor motor) {
  
//  shifted = shift_register.Shift_bytes();
//  Serial.println(shifted[container]);
//  shift_register.ShiftPrint(shifted);
  
  shifted = shift_register.Shift_bytes();
  Serial.println(shifted[container]);
  shift_register.ShiftPrint(shifted);
  
  motor.drive(speed);
  while (shifted[container] != 1) {
    shifted = shift_register.Shift_bytes();
    Serial.print(shifted[container]);
//        shift_register.ShiftPrint(shifted);       
    yield();  
    }
  motor.brake();
  Serial.println();
  shift_register.ShiftPrint(shifted);
  Serial.println("#######");
  delay(500);
  
  
  Serial.println("stop");
  }
 
//void movePenDown(int speed, Motor motor) {
//  Serial.println("Start motor");
//  motor.drive(speed);
//  while (!sensor.PressureCheck()) {
//    yield();
//    }
//    motor.brake();
//    pump.brake();
//  }




//
////  Serial.println("Base");
////  base.drive(600,1000);
//  
//  Serial.println("Vertical");
////  delay(1000);
//  pump.drive(600,1000);
//  v.drive(-600, 1000);
//  movePen(600,7,v);
//  pump.brake();
//  
//  Serial.println("Horizontal");
//  movePen(-1024,6,h);
//
//  Serial.println("Vertical");
////  delay(1000);
//  v.drive(-600, 1000);
//  movePen(600,7,v);
  
//
//  Serial.println("Vertical");
//  pump.drive(1024);
//  delay(1000);
//  v.drive(-600, 1000);
//  movePen(600,7,v);
//  pump.brake();
//  
//
//  Serial.println("Horizontal");
//  delay(1000);
//  movePen(1024,1,h);
//
//  Serial.println("Vertical");
//  pump.drive(1024);
//  delay(1000);
//  v.drive(-600, 1000);
//  movePen(600,7,v);
//  pump.brake();
//  
//  
//  Serial.println("Horizontal");
//  delay(1000);
//  movePen(-1024,5,h);
//
//  Serial.println("Vertical");
//  pump.drive(1024);
//  delay(1000);
//  v.drive(-600, 1000);
//  movePen(600,7,v);
//  pump.brake();
//  
//  Serial.println("Horizontal");
//  delay(1000);
//  movePen(1024,2,h);
//
//  Serial.println("Vertical");
//  pump.drive(1024);
//  delay(1000);
//  v.drive(-600, 1000);
//  movePen(600,7,v);
//  pump.brake();
//  
//  Serial.println("Horizontal");
//  delay(1000);
//  movePen(-1024,4,h);
//  
//  Serial.println("Vertical");
//  pump.drive(1024);
//  delay(1000);
//  v.drive(-600, 1000);
//  movePen(600,7,v);
//  pump.brake();
//  
//  
//  Serial.println("Horizontal");
//  delay(1000);
//  movePen(1024,3,h);

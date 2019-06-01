/*
 * Pill Dispencer project Arduino Side
 * Developed by:          Roberta Netzova
 * Last updated on:       19.04.09
 * Current version:       01.5
 * Working functionality: Base rotation; VP finding container; 
 *                        VP catching pill - With pressure class; 
 *                        main working flow; 
 *                        Check if pill has fallen in the way (pressure sensor validation)
 * ..................TODO:.......................
 * Check if pill has fallen in the index container (Shift register validation)
 * Connect with Internet (in adrduino_internet code);
*/


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

Motor base = Motor(IN1,IN2, PWMA);
//Motor pump = Motor(IN1, IN2, PWMB);
Motor h = Motor(IN1,IN2, PWMA1);
Motor v = Motor(IN1,IN2, PWMA2);
Shift_165 shift_register = Shift_165(enable, load, clock, data,register_number);
Sensor sensor = Sensor(A0);

int size = shift_register.get_register_size();

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
  while (!sensor.PressureCheck()) {
    pickPill(i);
    yield();
    }
    
   delay (500);
   movePen(-600,9,v);
   digitalWrite(pump,LOW);
   
   while (1) {
     if (shift_register.ShiftChecker(5000,8)) {
      Serial.println ("SUCCESS");
     break;
     }
     Serial.println ("FAIL");
     movePen(600,7,v);
     yield();
    
    }
    delay(2000);
    movePen(600,7,v);
     delay(2000);
  }
 
}
/*
 *................functions.................. 
 */
void pickPill (int cont) {
  
  movePen(1024,0,h);

  base.drive(-600,1000);
  
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
  
  Serial.println(shifted[container]);
  shift_register.ShiftPrint(shifted);
  
  motor.drive(speed);
  while (shifted[container] != 1) {
    shift_register.Shift_bytes(shifted);
    Serial.print(shifted[container]);     
    yield();  
    }
  
  motor.brake();
  Serial.println();
  shift_register.ShiftPrint(shifted);
  Serial.println("#######");
  
  Serial.println("stop");
  delay(1000);
  }
  

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
    motor.brake();
  }


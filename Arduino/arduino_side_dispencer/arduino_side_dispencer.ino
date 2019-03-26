/*
 * Pill Dispencer project Arduino Side
 * Developed by:     Roberta Netzova
 * Last updated on: 19.03.26
 * Current version: 01.1
 * Working functionality: Base rotation; Vacuum pren finding container
 * by number logic; catching pill (to do); 
 * 
*/
#include "motorDriver.h"
#include "shift_165.h"

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

const int neededContainer = 3;
const int exitContainer   = 0;
const int pillChecker     = 7;
Motor baseMotor = Motor(IN1, IN2, PWMA);
Motor penMotor = Motor(IN1, IN2, PWMB);
Motor vacuumPump = Motor(IN1, IN2, PWMA1);
Shift_165 shift_register = Shift_165(enable, load, clock, data);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start....");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Start loop....");
  // rotate base
  baseMotor.drive(500,2000);
  
  int* shifted = shift_register.Shift_bytes();

  // move pen right
  movePenHorizontally (1024, neededContainer);
  
  // vacuumPump on
  vacuumPump.drive(1024);
  
//  while (1) {
//    vacuumPump.drive(1024);
//    }
//    vacuumPump.drive(1024);

//  move pen to exit container

  movePenHorizontally (-1024, exitContainer);
  vacuumPump.brake();
  shifted = shift_register.Shift_bytes();
  if (shift_register.ShiftChecker(1500,pillChecker)) {
    Serial.println("Pill is delivered"); 
    } else Serial.println ("OOPS, Something went wrong");
}
/*
 *................functions.................. 
 */
void movePenHorizontally (int speed, int container) {
  int* shifted = shift_register.Shift_bytes();
  while (1) {
    penMotor.drive(speed);
    
    if (shifted[container] == 0) {
      penMotor.brake();
      break;
      }
    shifted = shift_register.Shift_bytes();
    }
  }

/******************************************************************************
TB6612.cpp
TB6612FNG H-Bridge Motor Driver Example code
Michelle @ SparkFun Electronics
8/20/16
https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library

Uses 2 motors to show examples of the functions in the library.  This causes
a robot to do a little 'jig'.  Each movement has an equal and opposite movement
so assuming your motors are balanced the bot should end up at the same place it
started.

Resources:
TB6612 SparkFun Library

Development environment specifics:
Developed on Arduino 1.6.4
Developed with ROB-9457
******************************************************************************/

#include "motorDriver.h"
#include <Arduino.h>

Motor::Motor(int In1pin, int In2pin, int PWMpin)
{
  In1 = In1pin;
  In2 = In2pin;
  PWM = PWMpin;
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(PWM, OUTPUT);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  
}

void Motor::drive(int speed)
{
  if (speed>=0) fwd(speed);
  else rev(-speed);
}
void Motor::drive(int speed, int duration)
{
  drive(speed);
  delay(duration);
  brake();
}

void Motor::fwd(int speed)
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, LOW);
   analogWrite(PWM, speed);

}

void Motor::rev(int speed)
{
   digitalWrite(In1, LOW);
   digitalWrite(In2, HIGH);
   analogWrite(PWM, speed);
}

void Motor::brake()
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, HIGH);
   analogWrite(PWM,0);
}

//void drive_both(Motor motor1, Motor motor2, int speed1, int speed2)
//{
//	motor1.drive(speed1);
//	motor2.drive(speed2);
//  delay(duration);
//  motor1.brake();
//  motor1.brake();
//}

//void brake(Motor motor1, Motor motor2)
//{
//	motor1.brake();
//	motor2.brake();
//}

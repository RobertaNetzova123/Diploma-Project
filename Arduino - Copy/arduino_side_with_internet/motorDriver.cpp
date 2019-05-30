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
  Serial.print("Motor drove ");
  Serial.print(duration);
  Serial.println(" seconds");
  delay(1000);
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
   delay(1000);
}

#include "pressureSensor.h"
#include <Arduino.h>

Sensor::Sensor(int PressurePin){
	pin = PressurePin;
  normal_state = 0.0;
}

float Sensor::readPressure(int pin){
  int pressureValue = analogRead(pin);
  float pressure = pressureValue;
//  Serial.println(pressure);
  return pressure;
  }

bool Sensor::PressureCheck(){
  float pressure = readPressure(pin);
  if(pressure != normal_state){
    Serial.println(pressure);
    return true;
    }
  return false;
  }
  
void Sensor::SetState(){
  normal_state = readPressure(pin);
  Serial.println(normal_state);
  }

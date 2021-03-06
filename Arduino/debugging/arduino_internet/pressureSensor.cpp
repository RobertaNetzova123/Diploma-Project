#include "pressureSensor.h"
#include <Arduino.h>

Sensor::Sensor(int PressurePin) {
	pin = PressurePin;
  normal_state = 0.0;
}

float Sensor::readPressure(int pin){
    int pressureValue = analogRead(pin);
//    float pressure=((pressureValue/1024.0)+0.095)/0.000009;
      float pressure = pressureValue;
    return pressure;
}

bool Sensor::PressureCheck(){
  //preventing unstable results
  delay(500);
  float pressure = readPressure(pin);
  if(pressure != normal_state){
    Serial.println(pressure);
    return true;
    }
  return false;
  }
void Sensor::SetState() {
  normal_state = readPressure(pin);
  }

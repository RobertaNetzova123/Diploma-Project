#ifndef pressureSensor_h
#define pressureSensor_h

#include <Arduino.h>

class Sensor {

public: 
	Sensor(int PressurePin); 
 
  bool PressureCheck ();
  float readPressure(int PressurePin);
  void SetState();
  
private:
	int pin;
  float normal_state;
};
#endif

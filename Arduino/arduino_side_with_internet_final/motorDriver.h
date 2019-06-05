#ifndef motorDriver_h
#define motorDriver_h

#include <Arduino.h>


class Motor {
  public:
    Motor(int In1pin, int In2pin, int PWMpin);      

  // Drive in direction given by sign, at speed given by magnitude of the 
	//parameter.
    void drive(int speed);  
	
	// drive(), but with a delay(duration)
    void drive(int speed, int duration);  
	
	//Stops motor by setting both input pins high
    void brake(); 
    
  private:
	int In1, In2, PWM;
	
	//private functions that spin the motor CC and CCW
	void fwd(int speed);
	void rev(int speed);
};

#endif

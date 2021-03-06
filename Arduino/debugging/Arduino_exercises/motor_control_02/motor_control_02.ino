
#include "lib.h"

#define AIN1 D6 
#define AIN2 D7
#define PWMA D8
#define PWMB D3

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA);
Motor motor2 = Motor(AIN1, AIN2, PWMB, offsetB);
void setup()
{

 Serial.begin(9600);
}


void loop()
{



    motor1.drive(1024);
//    delay(1000);
//    motor1.brake();
//    delay(500);
//    
//    motor2.drive(1024);
//   delay(1000);
//    motor2.brake();
//    delay(500);
//    
   
   
   //Use of the drive function which takes as arguements the speed
   //and optional duration.  A negative speed will cause it to go
   //backwards.  Speed can be from -255 to 255.  Also use of the 
   //brake function which takes no arguements.
//   motor2.drive(255,1000);
//   motor2.drive(-255,1000);
//   motor2.brake();
//   delay(1000);
//   
//   //Use of the forward function, which takes as arguements two motors
//   //and optionally a speed.  If a negative number is used for speed
//   //it will go backwards
//   forward(motor1, motor2, 150);
//   delay(1000);
//   
//   //Use of the back function, which takes as arguments two motors 
//   //and optionally a speed.  Either a positive number or a negative
//   //number for speed will cause it to go backwards
//   back(motor1, motor2, -150);
//   delay(1000);
//   
//   //Use of the brake function which takes as arguments two motors.
//   //Note that functions do not stop motors on their own.
//   brake(motor1, motor2);
//   delay(1000);
//   
//   //Use of the left and right functions which take as arguements two
//   //motors and a speed.  This function turns both motors to move in 
//   //the appropriate direction.  For turning a single motor use drive.
//   left(motor1, motor2, 100);
//   delay(1000);
//   right(motor1, motor2, 100);
//   delay(1000);
//   
//   //Use of brake again.
//   brake(motor1, motor2);
//   delay(1000);
   
}

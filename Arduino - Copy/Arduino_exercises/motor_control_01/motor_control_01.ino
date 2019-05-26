
#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 D6 
#define AIN2 D7
#define PWMA D8
#define STBY D1

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void setup()
{
 //Nothing here
//  pinMode(AIN1, OUTPUT);
//  pinMode(AIN2, OUTPUT);
//  pinMode(PWMA, OUTPUT);
//  pinMode(STBY, OUTPUT);
 Serial.begin(9600);
}


void loop()
{
   //Use of the drive function which takes as arguements the speed
   //and optional duration.  A negative speed will cause it to go
   //backwards.  Speed can be from -255 to 255.  Also use of the 
   //brake function which takes no arguements.
//
//   digitalWrite(AIN1, HIGH);
//   digitalWrite(AIN2, LOW);
//   analogWrite(PWMA, 255);
   
//   motor1.drive(255,1000);
////   motor1.brake();
////   delay(500);
//   motor1.drive(-255,1000);
//   motor1.brake();
    motor1.drive(700);
    delay(5000);
    motor1.brake();
   delay(500);
    motor1.drive(-700);
    delay(5000);
    motor1.brake();
   
   
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

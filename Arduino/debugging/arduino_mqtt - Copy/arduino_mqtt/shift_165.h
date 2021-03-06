#ifndef shift_165_h
#define shift_165_h

#include <Arduino.h>

class Shift_165 {
  public:
    Shift_165(int enablePin, int loadPin, int clockPin, int dataPin);
   //shifts bytes
    int* Shift_bytes();
  // shifts for specific duration and checks if specific pin has gone LOW. 
  //After the duration has ended exits the function with false result.
    bool ShiftChecker (int duration, int checker);
    void ShiftPrint(int* shifted);
   
  private:
    int enable, load, clock, data;

};

#endif

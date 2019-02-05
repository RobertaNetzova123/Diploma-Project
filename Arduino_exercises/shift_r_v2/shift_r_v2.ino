int latchPin = 5;
//Pin connected to SRCLK of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int dataPin = 7;

void setup() {
  //set pins to output so you can control the shift register
 Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  digitalWrite(latchPin, LOW);
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, LOW);
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, LOW);
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(5000);
  }
}

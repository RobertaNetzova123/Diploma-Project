/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/



void setup() {
  pinMode(D0, OUTPUT);   
  pinMode(D1, OUTPUT);   
  pinMode(D2, OUTPUT);   
  pinMode(D3, OUTPUT);   
  pinMode(D4, OUTPUT);   
  pinMode(D5, OUTPUT);   
  pinMode(D6, OUTPUT);   
  pinMode(D7, OUTPUT);   
  pinMode(D8, OUTPUT);   

  digitalWrite(D0,LOW);
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  

  Serial.begin(9600);
  Serial.println("Beginning ...");
}

// the loop function runs over and over again forever
void loop() {
//  int value = digitalRead(9);
//  Serial.println(value);
 
  digitalWrite(D0,LOW);
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);  // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is active low on the ESP-01)
  delay(500);                      // Wait for a second
  digitalWrite(D0,HIGH);
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,HIGH);
  digitalWrite(D8,HIGH);
  delay(500);                     
}

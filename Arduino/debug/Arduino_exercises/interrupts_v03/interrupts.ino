//interrupts v_03
//date: 08.02.19
//added connection logic between interrupt and bigger function
//NoInterrupt working but saving in mem)
//still triggered on both edges (most probably a hardware problem)


const int interruptPin = D2;
volatile byte interruptCounter = 0;
int numberOfInterrupts = 0;
volatile int IN = 0;

 
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
  Serial.begin(9600);
  pinMode(interruptPin, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
 
}
 
void handleInterrupt() {

  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
   // If interrupts come faster than 200ms, assume it's a bounce and ignore
   if (interrupt_time - last_interrupt_time > 200){
    
        interruptCounter++;
        IN ++;
   }
   last_interrupt_time = interrupt_time;

}

void blinkFunction() {

  for (int i  = 0; i < 5; i++) {
    
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);    
    Serial.println(i+1);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);  
  }
 }
void loop() {

  if(interruptCounter>0){
 
      interruptCounter--;
      numberOfInterrupts++;
 
      Serial.print("An interrupt has occurred. Total: ");
      Serial.println(numberOfInterrupts);
  }
  if (IN > 0) {
    noInterrupts();
      blinkFunction();
      IN --;
      digitalWrite(D1, LOW);
      delay(500);
      digitalWrite(D1, HIGH);
    interrupts();
  }
 
}

//interrupts v_02
//date: 07.02.19
//debouncer logic added
//still triggered on both efjes


const int interruptPin = D2;
volatile byte interruptCounter = 0;
int numberOfInterrupts = 0;
 
void setup() {
 
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
   }
   last_interrupt_time = interrupt_time;

}
 
void loop() {

  if(interruptCounter>0){
 
      interruptCounter--;
      numberOfInterrupts++;
 
      Serial.print("An interrupt has occurred. Total: ");
      Serial.println(numberOfInterrupts);
  }
 
}

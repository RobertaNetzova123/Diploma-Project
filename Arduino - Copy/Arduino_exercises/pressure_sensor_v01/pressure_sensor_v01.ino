 float last_state = 0.0;
 const int diode  = D1;
void setup() {
    Serial.begin(9600);
    pinMode(diode, OUTPUT);
    digitalWrite(diode, LOW); 
}
 
void loop(){
    float pressure = readPressure(A0);
    float millibars = pressure/100;
   
    
 if(last_state!= 0.0 && millibars!= last_state) {
    digitalWrite(diode,HIGH);
    delay(1000);
    digitalWrite(diode,LOW);
  }
 
    Serial.println();
//    Serial.print("Pressure = ");
//    Serial.print(pressure);
//    Serial.println(" pascals");
//    Serial.print("Pressure = ");
    Serial.print(millibars);
    Serial.println(" millibars");
    Serial.print(last_state);
    Serial.println("last state");
    last_state = millibars;
    
    delay(1000);
    
}
 
/* Reads pressure from the given pin.
* Returns a value in Pascals
*/
float readPressure(int pin){
    int pressureValue = analogRead(pin);
//    float pressure=((pressureValue/1024.0)+0.095)/0.000009;
      float pressure = pressureValue;
    return pressure;
}

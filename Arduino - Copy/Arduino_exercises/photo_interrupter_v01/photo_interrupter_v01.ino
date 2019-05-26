int CHECKER =  D6;
int diode  = D0;
int val = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CHECKER,INPUT);
  pinMode(diode,OUTPUT);
  digitalWrite(diode,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(CHECKER);
  Serial.println(val);
      if (val == 1) {
          digitalWrite(diode,LOW); 
        } else {
           digitalWrite(diode,HIGH);
      } 
}

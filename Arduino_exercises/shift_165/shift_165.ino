//shift register experiment
//coded by zxlee
//iamzxlee.wordpress.com

#define enable D1
#define load 1 //d3
#define clock D4
#define data D0
 
void setup(){

  pinMode(enable,FUNCTION_3);
  pinMode(enable,OUTPUT);
  pinMode(load,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,INPUT);
  digitalWrite(load,HIGH);
  digitalWrite(enable,HIGH);
  digitalWrite(clock,LOW);
  Serial.begin(9600);
  Serial.println();
  Serial.println("Begin...");
//  pinMode(LED_BUILTIN,OUTPUT);
//  digitalWrite(LED_BUILTIN,LOW);
}
 
void loop(){
  digitalWrite(load,LOW);
 delay(10);
  digitalWrite(load,HIGH);
   delay(10);
//  delayMicroseconds(5);
//  
  digitalWrite(clock,HIGH);
  digitalWrite(enable,LOW);
  byte incoming=shiftIn(data,clock,MSBFIRST);
  digitalWrite(enable,HIGH);
   
  for(int i=7;i>=0;i--){
//int i = 7;
    if(bitRead(incoming,i)==1)
    {
      Serial.print("1");
    }
   else
    {
      Serial.print("0");
    }
  }
  Serial.println();
}

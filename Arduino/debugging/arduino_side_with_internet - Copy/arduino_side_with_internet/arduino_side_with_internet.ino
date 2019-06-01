/*
 * Pill Dispencer project Arduino Side
 * Developed by:          Roberta Netzova
 * Last updated on:       19.05.30del
 * Current version:       01.07
 * Working functionality: Base rotation; VP finding container; 
 *                        VP catching pill - With pressure class; 
 *                        main working flow; 
 *                        Check if pill has fallen in the way (pressure sensor validation)
 *                        Check if pill has fallen in the index container (Shift register validation)
 *                        Connect with Internet (in adrduino_internet code);
 * ..................TODO:.......................
 * Optimize delays
 * fix endless while in case of error
 * add comments
 * Fix case when dispencer is empty
 * 
*/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

#include "mqtt.h"
#include "motorDriver.h"
#include "pressureSensor.h"
#include "shift_165.h"

const int pin  = A0;
#define IN1   D6 
#define IN2   D7
#define PWMA  D4 //base
#define pump  D3 //PUMP
#define PWMA1 D2 // pump
#define PWMA2 D5

#define enable D1
#define load   1 //GPIO3
#define clock  D8
#define data   D0

#define register_number 2

int neededContainer =  0;
const int local_id            = 1;
const String mqtt_id          = "Dispenser:" + String(local_id);
const int mqtt_port           = 1883;
const char* mqtt_server       = "rety.dynu.net";

const String in_topic    = "server-dispenser";
const String out_topic   = "outTopic";

WiFiServer server(81);
Mosquitto mosquitto = Mosquitto(mqtt_server, mqtt_port, mqtt_id, in_topic, out_topic);

Motor base = Motor(IN1,IN2, PWMA);
Motor h = Motor(IN1,IN2, PWMA1);
Motor v = Motor(IN1,IN2, PWMA2);

Sensor sensor = Sensor(A0);
Shift_165 shift_register = Shift_165(enable, load, clock, data,register_number);
int size = shift_register.get_register_size();

void setup() {
  
  Serial.begin(9600);
  pinMode(pump, OUTPUT);
  digitalWrite(pump,LOW);

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("Connected.");

  Serial.println("Connecting mosquitto broker");
  mosquitto.mqtt_setup();
  mosquitto.setCallback(mqttCallback);
  
  delay(500);
  sensor.SetState();
  int shifted[size];
  shift_register.Shift_bytes(shifted);
}

void loop(){
  
   if(! mosquitto.read()) Serial.println("Failed to read !!!");
   
  }


void mqttCallback(char* topic, byte* payload, unsigned int length)
{
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//  Serial.println(".....");

  String msg;
  for (int i = 0; i < length; i++)
  {
//    Serial.print((char) payload[i]);
    msg += (char) payload[i];
  }

//  Serial.println();

  String tmp = msg.substring(5);
  if(tmp.indexOf(":") <= 0)
    {
      mosquitto.publish("error");
      return;
    }
  
  int container = (tmp.substring(0, tmp.indexOf(":"))).toInt();
  int count = (tmp.substring(tmp.indexOf(":") + 1)).toInt();
  if (count > 0) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println(".....");
    Serial.print("container ");
    Serial.println(container);
    Serial.print("count ");
    Serial.println(count);
    }
    
  neededContainer = container;
  for (int i = 0; i < count; i++) {
    sensor.SetState();
    delay(1000);
    while (!sensor.PressureCheck()) {
      pickPill(neededContainer);
      delay(100);
      yield();
      }

     delay (100);
     movePen(-600,9,v);
     digitalWrite(pump,LOW);
   
     while (1) {
       if (shift_register.ShiftChecker(5000,8)) {
        Serial.println ("SUCCESS");
       break;
       }
       Serial.println ("FAIL");
       movePen(600,7,v);
       yield();
      }
      
      delay(2000);
      movePen(600,7,v);
      delay(2000);
  }
}

/*
 *................functions.................. 
 */
void pickPill (int cont) {
  
  movePen(1024,0,h);

  base.drive(-600,2500);
  
  movePen(-1024,cont,h);
 
  
  digitalWrite(pump,HIGH);
  delay(500);
  
  int i = 0;
  for (; i <  3; i++) {
      base.drive(-600,1000);
      movePenDown(-600,v);
      delay(500);
      movePen(600,7,v);
   if (sensor.PressureCheck()) break;
  }
  
  movePen(600,7,v);
  
  movePen(1024,0,h);
 
}

void movePen(int speed, int container, Motor motor) {
  
  int shifted[size];
  shift_register.Shift_bytes(shifted);
  
  Serial.println(shifted[container]);
  shift_register.ShiftPrint(shifted);
  delay(500);
  
  motor.drive(speed);
  while (shifted[container] != 1) {
    shift_register.Shift_bytes(shifted);
    Serial.print(shifted[container]);     
    yield();  
    }
  
  motor.brake();
  Serial.println();
  shift_register.ShiftPrint(shifted);
  Serial.println("#######");
  Serial.println("stop");
  delay(500);
  }
  

void movePenDown(int speed, Motor motor) {
  
  int shifted[size];
  shift_register.Shift_bytes(shifted);
  shift_register.ShiftPrint(shifted);
  delay(500);
  
  Serial.println("Start motor");
  motor.drive(speed);
 
  while (!sensor.PressureCheck()) {
     shift_register.Shift_bytes(shifted);
    Serial.print(shifted[9]);
     if (shifted[9] == 1) break;
     yield();
    }
    motor.brake();
    delay(500);
  }
